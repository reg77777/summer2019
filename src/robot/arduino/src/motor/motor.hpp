#ifndef INCLUDE_MOTOR_HPP
#define INCLUDE_MOTOR_HPP

class Motor{
    private:
        int pinA_,pinB_;
    public:
        Motor(int pinA,int pinB);
        void run(int speed);
};

#endif
