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

int Encoders::a[4]={2,19,3,21};
int Encoders::b[4]={39,22,47,40};
int Encoders::gnd[4]={37,24,49,41};
int Encoders::v[4]={35,26,51,42};
int Encoders::intpins[4]={0,4,1,3};
volatile long long int Encoders::counts[4]={0,0,0,0};

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
    attachInterrupt(intpins[3],Cb3,RISING);
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
void Encoders::Cb3(){
    if(digitalRead(b[3]))counts[3]--;
    else counts[3]++;
}

void Encoders::reset(int x){
    counts[x]=0;
}

#endif
