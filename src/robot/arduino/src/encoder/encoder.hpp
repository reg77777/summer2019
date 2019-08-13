#ifndef INCLUDE_ENCODER_HPP
#define INCLUDE_ENCODER_HPP

#include "Arduino.h"

class Encoder{
    private:
        int pinA_,pinB_;
        volatile long long int count=0;
    public:
        Encoder(int pinA,int pinB,void(*)());
        void(*callback)();
};

#endif
