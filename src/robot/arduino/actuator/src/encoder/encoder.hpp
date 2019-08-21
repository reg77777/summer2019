#ifndef INCLUDE_ENCODER_HPP
#define INCLUDE_ENCODER_HPP

#include "Arduino.h"

class Encoders{
    public:
        Encoders();
        static int a[];
        static int b[];
        static int intpins[];
        static volatile long long int counts[];
        static void callback0();
        static void callback1();
        static void callback2();
        void reset();
};

int Encoders::a[3]={2,3,18};
int Encoders::b[3]={22,24,26};
int Encoders::intpins[3]={0,1,2};
volatile long long int Encoders::counts[3]={0,0,0};

Encoders::Encoders(){
    for(int i=0;i<3;i++){
        pinMode(a[i],INPUT_PULLUP);
        pinMode(b[i],INPUT_PULLUP);
    }
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

void Encoders::reset(){
    for(int i=0;i<3;i++)counts[i]=0;
}

#endif
