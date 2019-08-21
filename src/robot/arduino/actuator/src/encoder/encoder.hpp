#ifndef INCLUDE_ENCODER_HPP
#define INCLUDE_ENCODER_HPP

#include "Arduino.h"

class Encoders{
    public:
        static int b[3];
        static int intpins[3];
        static volatile long long int counts[3];
        static void setup();
        static void callback0();
        static void callback1();
        static void callback2();
};

#endif
