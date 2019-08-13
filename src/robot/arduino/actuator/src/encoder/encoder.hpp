#ifndef INCLUDE_ENCODER_HPP
#define INCLUDE_ENCODER_HPP

#include "Arduino.h"

class Encoder{
    private:
        volatile long long int count=0;
    public:
        Encoder(void(*)());
        void(*callback)();
};

#endif
