#include "motorcontrol.h"
#include "Arduino.h"

motorcontrol::motorcontrol(int p1, int p2, int ch1, int ch2, int e1, int e2):d(p1, p2, ch1, ch2), e(e1, e2){

    kp = 7;
    kd = 0.001;
    ki = 0;

    eprev = 0;
    ep = 0;
    ed = 0;
    ei = 0;

    velocity_prev = 0;
    velocity_curr = 0;
    curr_T = 0;
    prev_T = 0;
}

void motorcontrol::refresh(){

    ei = 0;

    velocity_curr = 0;
    velocity_prev = 0;
}

void motorcontrol::init(){
    
    refresh();
    d.init();
    e.init();

    curr_T = micros();
    prev_T = curr_T;
}

void motorcontrol::update_state(){

    velocity_prev = velocity_curr;
    velocity_curr = e.get_vel();

    prev_T = curr_T;
    curr_T = micros();
}

void motorcontrol::setvel_setpoint(float vel, char dir){

    update_state();

    ep = vel - velocity_curr;
    ei += ep*(curr_T - prev_T)/(1.0e6);
    ed = (ep - eprev)/((curr_T - prev_T)/(1.0e6));

    if(ei > abs(0.4*ep)){ei = 0;}

    int duty = kp*ep + kd*ed + ki*ei;

    if(duty > 4095){ duty = 4095;}
    if(duty < 0){ duty = 0;}

    d.setDir(dir);
    d.drive(duty);

    eprev = ep;
}

float motorcontrol::get_velocity(){

  return e.get_vel();
}