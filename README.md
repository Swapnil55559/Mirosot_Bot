
# Mirosot

This repository houses the comprehensive design and documentation for an autonomously controlled bot, encompassing the following key components:

#### Board Design and Schematic:

 - Employs an ESP32 microcontroller as the foundation of the main circuit board.
 - Faulhaber Series 2224SR encoded brushed DC motors are used (Having 6 pinout: +M, -M, +5V, GND, Encoder A and Encoder B)
 - DRV8833 Motor driver and buck converter is used (Requires 3S Lipo battery).
 - 5V logic level shifting to 3.3 logic level for Encoder using diodes in reverse bias
 - DRV8833 is always enabled by shorting the JP jumper at the back of the breakout board
 - Extra GPIO LED are added, one of which is for low battery voltage warning (Battery voltage is read by ESP32)

#### Embedded Code:

 - Implements wireless communication using the UDP protocol.
 - Based on position the bot as a UDP client receives velocity commands for both wheels.
 - Leverages a precise velocity control algorithm (PID controller) to achieve the specified RPM and direction.
 - The velocity is read by counting the number of pulses in 1ms (each pulse triggers an interrupt on rising edge and increments the counter of pulse)
 - There are three header files included, "driver.h", "encoder.h", and "motorcontrol.h". The latter depends on the former two.

## Connections

* Motor +M and -M pins are connected to GPIO 25 and 26 or 33 and 32 of ESP32
* Motor Encoder A and Encoder B pins are connected to GPIO 18 and 19 or 36 and 39
* Battery refernce voltage is connected Analog Input pin 35 (12 bit resolution)
* GPIO LED are connected to GPIO pins 13, 14 and 27. The battery low voltage warning LED is connected to GPIO 12

## Instructions

In order to use this header for motor control, first make sure you have the proper connections, as explained above. Then, just `#include "motorcontrol.h"` and initialise a **motorcontrol** object as
`motorcontrol objectname(M+, M-, Channel 1, channel 2, Encoder pin 1, Encoder pin 2)`

`Channel 1` is the PWM channel that is going to be used\
`Channel 2` another PWM channel to drive the motor according to the calculated duty cycle

This object has the following public member functions:

* `void init()` initialises the **motorcontrol** object

* `void refresh()` sets the current velocity and previous velocity as 0

* `void update_state()` updates the previous velocity and previous time counter, assigns current velocity and current time counter

* `float get_velocity()` return the current velocity 
* `void setvel_setpoint(float vel, char dir)` excecutes a single loop of velocity control, calculates proportional, dervative and integral error, then computes the duty cycle and drives the motor with calculated duty cycle.
* `kp`, `kd` and `ki` are public class members, thus we can have tune both the motors independantly. object of class `driver` and `encoder` is also public member of `motorcontrol` class because we need to call `cal_vel_callback()` method of class `encoder` in ISR
Inside the `ino` file we need to initialise UDP class by using header files `#include  <WiFiUdp.h>` and `#include <WiFi.h>` then define the `WIFI_SSID`, `WIFI_PASSWORD` and `UDP_PORT`