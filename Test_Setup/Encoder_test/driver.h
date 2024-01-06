#ifndef driver_h
#define driver_h

#include "Arduino.h"

class driver{

  private:
    int pwm1;
    int pwm2;
    int pwm_channel1;
    int pwm_channel2;
    char dir;
    bool rev;

  public:
    driver(int p1, int p2, int p3, int p4);
    void init();
    void setDir(char d);
    void drive(int duty);
    void reverse();
};

#endif