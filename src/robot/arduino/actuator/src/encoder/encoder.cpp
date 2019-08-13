#include "encoder.hpp"
#include "Arduino.h"

int interruptPins[6]={2,3,21,20,19,18};

Encoder::Encoder(int pinA,void(*func)()){
    callback=func;
    attachInterrupt(pinA,callback,RISING);
}
