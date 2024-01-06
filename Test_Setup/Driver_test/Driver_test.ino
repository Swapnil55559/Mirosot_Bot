#include "driver.h"

driver d1(25, 26, 0, 1);

void setup() {
  
  d1.init();

}

void loop() {
  // put your main code here, to run repeatedly:
  d1.setDir('c');
  d1.drive(1000);
  delay(1000);
  d1.reverse();
  // d1.setDir('a');
  // d1.drive(1000);
  // delay(1000);

}
