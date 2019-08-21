#include "encoder.hpp"
#include "Arduino.h"

void Encoders::setup(){
    b[0]=20;
    b[1]=21;
    b[2]=22;
    intpins[0]=0;
    intpins[1]=1;
    intpins[2]=2;
    attachInterrupt(intpins[0],callback0,RISING);
    attachInterrupt(intpins[1],callback1,RISING);
    attachInterrupt(intpins[2],callback2,RISING);
}

void Encoders::callback0(){
    if(digitalRead(b[0]))counts[0]++;
    else counts[0]--;
}

void Encoders::callback1(){
    if(digitalRead(b[1]))counts[1]++;
    else counts[1]--;
}

void Encoders::callback2(){
    if(digitalRead(b[2]))counts[2]++;
    else counts[2]--;
}
