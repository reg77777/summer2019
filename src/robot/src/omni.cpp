#include <ros/ros.h>
#include <math.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Int32.h>

//   0     up
//          
// 1   2  down
//
// CW +  CCW -
        
class Omni{
    private:
        ros::NodeHandle nh;

        ros::Publisher mtPb[3]={
            nh.advertise<std_msgs::Float32>("mt0",1),
            nh.advertise<std_msgs::Float32>("mt1",1),
            nh.advertise<std_msgs::Float32>("mt2",1)
        };

        void omni_callback(const geometry_msgs::Twist::ConstPtr& msg);
        ros::Subscriber omni_sub=nh.subscribe<geometry_msgs::Twist>("omni",10,&Omni::omni_callback,this);


        void mtRun(int num,float spd);

        //rough directioin
        void front(float spd);
        void back(float spd);
        void left(float spd);
        void right(float sed);
        void frontleft(float spd);
        void frontright(float spd);
        void backleft(float spd);
        void backright(float spd);
        void roatate(float spd);

        void stop();

        //fine direction
        void move(float rad,float spd);
};

void Omni::mtRun(int num,float spd){
    std_msgs::Float32 mg;
    mg.data=spd;
    mtPb[num].publish(mg);
}

void Omni::front(float spd){
    mtRun(0,0);
    mtRun(1,-spd);
    mtRun(2,spd);
}

void Omni::back(float spd){
    mtRun(0,0);
    mtRun(1,spd);
    mtRun(2,-spd);
}

void Omni::left(float spd){
    mtRun(0,spd);
    mtRun(1,-spd);
    mtRun(2,-spd);
}

void Omni::right(float spd){
    mtRun(0,-spd);
    mtRun(1,spd);
    mtRun(2,spd);
}

void Omni::frontleft(float spd){
    mtRun(0,spd);
    mtRun(1,-spd);
    mtRun(2,0);
}

void Omni::frontright(float spd){
    mtRun(0,-spd);
    mtRun(1,0);
    mtRun(2,spd);
}

void Omni::backleft(float spd){
    mtRun(0,spd);
    mtRun(1,0);
    mtRun(2,-spd);
}

void Omni::backright(float spd){
    mtRun(0,-spd);
    mtRun(1,spd);
    mtRun(2,0);
}

void Omni::stop(){
    mtRun(0,0);
    mtRun(1,0);
    mtRun(2,0);
}

void Omni::omni_callback(const geometry_msgs::Twist::ConstPtr& mg){
    geometry_msgs::Vector3 linear=mg->linear;
    //geometry_msgs::Vector3 angular=mg->angular;
    float x=linear.x;
    float y=linear.y;
    float spd=(x+y)/2;
    if(x>0&&y>0)frontright(spd);
    else if(x==0&&y>0)front(spd);
    else if(x<0&&y>0)frontleft(spd);
    else if(x<0&&y==0)left(spd);
    else if(x<0&&y<0)backleft(spd);
    else if(x==0&&y<0)back(spd);
    else if(x>0&&y<0)backright(spd);
    else if(x>0&&y==0)right(spd);
    else stop();
}

int main(int argc,char**argv){
    ros::init(argc,argv,"omni");
    Omni omni;
    ros::spin();
    return 0;
}
