#include "encoder.hpp"
#include "Arduino.h"

int interruptPins[6]={2,3,21,20,19,18};

Encoder::Encoder(int pinA,int pinB,void(*func)()){
    callback=func;
    pinA_=pinA;
    pinB_=pinB;
    attachInterrupt(pinA,callback,RISING);
}
