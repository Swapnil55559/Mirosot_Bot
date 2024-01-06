#include "driver.h"
#include "Arduino.h"

driver::driver(int p1, int p2, int p3, int p4){

    pwm1 = p1;
    pwm2 = p2;
    pwm_channel1 = p3;
    pwm_channel2 = p4;

    dir = 'c';
    rev = false;
}

void driver::init(){
    
    ledcSetup(pwm_channel1, 1000, 12);
    ledcAttachPin(pwm1, pwm_channel1);
    ledcWrite(pwm_channel1, 0);

    ledcSetup(pwm_channel2, 1000, 12);
    ledcAttachPin(pwm2, pwm_channel2);
    ledcWrite(pwm_channel2, 0);
}

void driver::setDir(char d){

    dir = d;
}

void driver::drive(int duty){

    if(!rev){

        if(dir == 'c'){
            ledcWrite(pwm_channel1, duty);
            ledcWrite(pwm_channel2, 0);
        }

        else if(dir == 'a'){
            ledcWrite(pwm_channel1, 0);
            ledcWrite(pwm_channel2, duty);
        }
    }

    else{
        
        if(dir == 'a'){
            ledcWrite(pwm_channel1, duty);
            ledcWrite(pwm_channel2, 0);
        }

        else if(dir == 'c'){
            ledcWrite(pwm_channel1, 0);
            ledcWrite(pwm_channel2, duty);
        }
    }
}

void driver::reverse(){

    rev = !rev;
}