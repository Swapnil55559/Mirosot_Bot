#include "encoder.h"
#include "Arduino.h"

encoder::encoder(int e1, int e2){

    encd1 = e1;
    encd2 = e2;
    pulse = 0;
    velocity = 0;
}

encoder::init(){

    pinMode(encd1, INPUT);
    pinMode(encd2, INPUT);

    current_time = micros();
    previous_time = current_time;
}

encoder::get_vel(){

    return velocity;
}

encoder::cal_vel_callback(){

    pulse=pulse+1;
    current_time=micros();
    
    if(current_time-previous_time>1000){

        velocity=(60000.0*pulse)/(1024.0);
        previous_time=current_time;
        pulse=0;
    }
}