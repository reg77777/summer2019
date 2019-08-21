#include <ros/ros.h>
#include <math.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Int32.h>

class Omni{
    public:
        Omni();

        //   0     up
        //          
        // 1   2  down
        //
        // CW +  CCW -
        ros::Publisher motor_pub[3]={
            nh.advertise<std_msgs::Float32>("mt0",1),
            nh.advertise<std_msgs::Float32>("mt1",1),
            nh.advertise<std_msgs::Float32>("mt2",1)
        };

        void motor_run(int num,int speed);

        ros::Subscriber omni_sub=nh.subscribe<geometry_msgs::Twist>("omni",10,&Omni::omni_callback,this);
        void omni_callback(const geometry_msgs::Twist::ConstPtr& msg);

    private:
        ros::NodeHandle nh;
        void up(int speed);
        void down(int speed);
        void left(int speed);
        void right(int speed);
        void move(int rad,int speed);
        void roatate(int speed);
};

Omni::Omni(){
}

void Omni::motor_run(int num,int speed){
    std_msgs::Int32 msg;
    msg.data=speed;
    motor_pub[num].publish(msg);
}

void Omni::up(int speed){
    motor_run(1,-speed);
    motor_run(2,speed);
}

void Omni::down(int speed){
    motor_run(1,speed);
    motor_run(2,-speed);
}

void Omni::left(int speed){
    motor_run(0,speed);
    motor_run(1,-speed);
    motor_run(2,-speed);
}

void Omni::right(int speed){
    motor_run(0,-speed);
    motor_run(1,speed);
    motor_run(2,speed);
}

void Omni::omni_callback(const geometry_msgs::Twist::ConstPtr& msg){
}

int main(int argc,char**argv){
    ros::init(argc,argv,"omni");
    Omni omni();
    ros::spin();
    return 0;
}
