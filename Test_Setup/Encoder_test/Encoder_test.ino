#include "encoder.h"
#include "driver.h"

driver d1(25, 26, 0, 1);
encoder e1(18, 19);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  d1.init();
  e1.init();

  d1.drive(1000);

  attachInterrupt(18, int_handler_1, RISING);
  attachInterrupt(19, int_handler_1, RISING);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(e1.get_vel());
  delay(10);
}

void int_handler_1(){

  e1.cal_vel_callback();
}
