#include <ros/ros.h>
#include <math.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Int32.h>
#include <cmath>
#include <algorithm>

class Move{
    public:
        Move();
        void publish();
    private:
        ros::NodeHandle nh;

        ros::Publisher velPb=nh.advertise<geometry_msgs::Twist>("cmd_vel",1);

        void mvCb(const geometry_msgs::Twist::ConstPtr&mg);
        ros::Subscriber mvSb=nh.subscribe<geometry_msgs::Twist>("cmd_move",10,&Move::mvCb,this);

        ros::Publisher vPb=nh.advertise<geometry_msgs::Twist>("cmd_vel",1); 

        void e0Cb(const std_msgs::Int32::ConstPtr&mg);
        void e1Cb(const std_msgs::Int32::ConstPtr&mg);
        void e2Cb(const std_msgs::Int32::ConstPtr&mg);
        ros::Subscriber e0Sb=nh.subscribe<std_msgs::Int32>("enc0",10,&Move::e0Cb,this);
        ros::Subscriber e1Sb=nh.subscribe<std_msgs::Int32>("enc1",10,&Move::e1Cb,this);
        ros::Subscriber e2Sb=nh.subscribe<std_msgs::Int32>("enc2",10,&Move::e2Cb,this);
        long long int e0c=0;
        long long int e1c=0;
        long long int e2c=0;
        float x=0,y=0,z=0;
        double kp;
        double maxspd;
        double r;
};

Move::Move(){
    nh.param<double>("kp",kp,0.1);
    nh.param<double>("maxspd",maxspd,80);
    nh.param<double>("r",r,0.1);
}

void Move::e0Cb(const std_msgs::Int32::ConstPtr&mg){
    e0c=mg->data;
}
void Move::e1Cb(const std_msgs::Int32::ConstPtr&mg){
    e1c=mg->data;
}
void Move::e2Cb(const std_msgs::Int32::ConstPtr&mg){
    e2c=mg->data;
}

void Move::mvCb(const geometry_msgs::Twist::ConstPtr&mg){
    x=mg->linear.x;
    y=mg->linear.y;
    z=mg->angular.z;
}

void Move::publish(){
    geometry_msgs::Twist mg;
    float nowx= -e0c +e1c*sqrt(3)/2  +e2c*sqrt(3)/2;
    float nowy=      -e1c/2          +e2c/2;
    float nowz= e0c  +e1c            +e2c;
    nowx/=3;nowy/=2;nowz/=3;
    mg.linear.x=kp*(x-nowx);
    mg.linear.y=kp*(y-nowy);
    mg.angular.z=r*(z-nowz);

    //spd max limit
    if(mg.linear.x>=0)mg.linear.x=std::min(mg.linear.x,maxspd);
    else mg.linear.x=std::max(mg.linear.x,-maxspd);
    if(mg.linear.y>=0)mg.linear.y=std::min(mg.linear.y,maxspd);
    else mg.linear.y=std::max(mg.linear.y,-maxspd);
    if(mg.linear.z>=0)mg.angular.z=std::min(mg.angular.z,maxspd);
    else mg.angular.z=std::max(mg.angular.z,-maxspd);

    vPb.publish(mg);
}

int main(int argc,char**argv){
    ros::init(argc,argv,"move");
    Move move;
    ros::Rate loop_rate(5);
    while(ros::ok()){
        move.publish();
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}
