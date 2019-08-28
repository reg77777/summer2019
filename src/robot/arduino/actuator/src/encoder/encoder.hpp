#ifndef INCLUDE_ENCODER_HPP
#define INCLUDE_ENCODER_HPP

#include "Arduino.h"

class Encoders{
    public:
        Encoders();
        static int a[];
        static int b[];
        static int v[];
        static int gnd[];
        static int intpins[];
        static volatile long long int counts[];
        static void Cb0();
        static void Cb1();
        static void Cb2();
        static void Cb3();
        void reset(int x);
};

int Encoders::a[3]={2,3,19};
int Encoders::b[3]={39,47,22};
int Encoders::gnd[3]={37,49,24};
int Encoders::v[3]={35,51,26};
int Encoders::intpins[3]={0,1,4};
volatile long long int Encoders::counts[3]={0,0,0};

Encoders::Encoders(){
    for(int i=0;i<3;i++){
        pinMode(a[i],INPUT_PULLUP);
        pinMode(b[i],INPUT_PULLUP);
    }
    for(int i=0;i<3;i++){
        pinMode(v[i],OUTPUT);
        digitalWrite(v[i],HIGH);
        pinMode(gnd[i],OUTPUT);
        digitalWrite(gnd[i],LOW);
    }
    attachInterrupt(intpins[0],Cb0,RISING);
    attachInterrupt(intpins[1],Cb1,RISING);
    attachInterrupt(intpins[2],Cb2,RISING);
}

void Encoders::Cb0(){
    if(digitalRead(b[0]))counts[0]--;
    else counts[0]++;
}
void Encoders::Cb1(){
    if(digitalRead(b[1]))counts[1]--;
    else counts[1]++;
}
void Encoders::Cb2(){
    if(digitalRead(b[2]))counts[2]--;
    else counts[2]++;
}

void Encoders::reset(int x){
    counts[x]=0;
}

#endif
