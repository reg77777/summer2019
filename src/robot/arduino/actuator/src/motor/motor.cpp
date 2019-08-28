#include "Arduino.h"
#include "motor.hpp"

Motor::Motor(int pinA,int pinB){
    pinA_=pinA;
    pinB_=pinB;
    pinMode(pinA_,OUTPUT);
    pinMode(pinB_,OUTPUT);
}

void Motor::run(int speed){
    if(speed>255)speed=255;
    if(speed<-255)speed=-255;
    if(speed>=0){
        analogWrite(pinA_,speed);
        analogWrite(pinB_,0);
    }
    else{
        analogWrite(pinA_,0);
        analogWrite(pinB_,-speed);
    }
}
