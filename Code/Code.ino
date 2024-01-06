#include <stdio.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <math.h>
#include "driver.h"
#include "encoder.h"
#include "motorcontrol.h"

// Set WiFi credentials
#define WIFI_SSID "YOUR_SSID"
#define WIFI_PASS "YOUR_PASSWORD"
#define UDP_PORT 12345

#define LED1  13
#define LED2  14
#define LED3  27
#define BATT_LED  12
#define VCC_REF   35

WiFiUDP UDP;

// Declearing motorcontrol object
motorcontrol m1(25, 26, 0, 1, 18, 19); //(M+, M-, Channel 1, channel 2, Encoder pin 1, Encoder pin 2)
motorcontrol m2(33, 32, 2, 3, 36, 39); //(M+, M-, Channel 1, channel 2, Encoder pin 1, Encoder pin 2)

char packet[10];
float rpm1 = 0;
float rpm2 = 0;
char dir1, dir2;
float batt_volt;

void setup(){

  Serial.begin(115200);
  Serial.println();

  pinMode(BATT_LED, OUTPUT);
  pinMode(VCC_REF, INPUT);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  digitalWrite(BATT_LED, LOW);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);


  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(LED1, HIGH);
    delay(250);
    digitalWrite(LED1, LOW);
    delay(250);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());

  // Begin listening to UDP port
  UDP.begin(UDP_PORT);
  Serial.print("Listening on UDP port ");
  Serial.println(UDP_PORT);

  m1.init();
  m2.init();


  attachInterrupt(18, int_handler_1, RISING);
  attachInterrupt(19, int_handler_1, RISING);
  attachInterrupt(36, int_handler_2, RISING);
  attachInterrupt(39, int_handler_2, RISING);
}

void loop(){

  batt_volt = ((183.0/43.0)*(analogRead(VCC_REF)*(3.5/4095.0)) + 1.0);

  int packetSize = UDP.parsePacket();
  if (packetSize) {

    int len = UDP.read(packet,10);

    if (len > 0) {
      packet[len] = '\0';
    }
    
    rpm1 = (((int)(packet[1])- 48)*pow(10,3) + ((int)(packet[2])- 48)*pow(10,2) + ((int)(packet[3])- 48)*pow(10,1)+ ((int)(packet[4])- 48)) ;
    rpm2 = (((int)(packet[6])- 48)*pow(10,3) + ((int)(packet[7])- 48)*pow(10,2) + ((int)(packet[8])- 48)*pow(10,1)+ ((int)(packet[9])- 48)) ;
   
    if( packet[0] == '-'){dir1 = 'a';}
    else {dir1 = 'c';}

    if( packet[5] == '-'){dir2 = 'a';}
    else {dir2 = 'c';}
  }

  m1.setvel_setpoint(rpm1, dir1);
  m2.setvel_setpoint(rpm2, dir2);
}

//Interrupt Service Routine
void int_handler_1() {m1.e.cal_vel_callback();}

void int_handler_2() {m2.e.cal_vel_callback();}
