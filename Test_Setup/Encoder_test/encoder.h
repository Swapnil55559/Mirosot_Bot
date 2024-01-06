#ifndef encoder_h
#define encoder_h

#include "Arduino.h"

class encoder{

    private:
        long long pulse;
        float velocity;
        int encd1;
        int encd2;
        unsigned long current_time;
        unsigned long previous_time;

    public:
        encoder(int e1, int e2);
        void init();
        float get_vel();
        void cal_vel_callback();
};

#endif