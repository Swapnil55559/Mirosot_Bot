#include "driver.h"
#include "encoder.h"
#include "motorcontrol.h"

motorcontrol m1(25, 26, 0, 1, 18, 19);
//motorcontrol m2(32, 33, 2, 3, 36, 39);

void setup(){

  Serial.begin(115200);

  m1.init();
  //m2.init();

  attachInterrupt(18, int_handler_1, RISING);
  attachInterrupt(19, int_handler_1, RISING);
  // attachInterrupt(36, int_handler_2, RISING);
  // attachInterrupt(39, int_handler_2, RISING);
}

void loop(){

  m1.setvel_setpoint(5000, 'c');
//  m2.setvel_setpoint(5000, 'c');
  
  Serial.print(0); Serial.print(",");
  Serial.print(5000); Serial.print(",");
  Serial.println(m1.get_velocity());
}

void int_handler_1(){

  m1.e.cal_vel_callback();
}

// void int_handler_2(){

//   m2.e.cal_vel_callback();
// }