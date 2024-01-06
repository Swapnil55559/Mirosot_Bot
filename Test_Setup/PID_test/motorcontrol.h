#include "driver.h"
#include "encoder.h"

#ifndef motorcontrol_h
#define motorcontrol_h

#include "Arduino.h"

class motorcontrol{
    private:
        float velocity_curr;
        float velocity_prev;
        float kp;
        float kd;
        float ki;

        float eprev;
        float ep;
        float ed;
        float ei;
        unsigned long curr_T;
        unsigned long prev_T;

    public:
        encoder e;
        driver d;

        motorcontrol(int p1, int p2, int ch1, int ch2, int e1, int e2);
        void refresh();
        void init();
        void update_state();
        void setvel_setpoint(float vel, char d);
        float get_velocity();
};

#endif