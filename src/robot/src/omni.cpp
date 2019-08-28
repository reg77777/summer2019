#include <ros/ros.h>
#include <math.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Int32.h>
#include <cmath> 
//   0     up
//          
// 1   2  down
//
// CW +  CCW -
        
class Omni{
    private:
        ros::NodeHandle nh;

        //motor publisher
        ros::Publisher mtPb[3]={
            nh.advertise<std_msgs::Float32>("mt0",1),
            nh.advertise<std_msgs::Float32>("mt1",1),
            nh.advertise<std_msgs::Float32>("mt2",1)
        };

        //cmd subscriber
        void cmdVelCb(const geometry_msgs::Twist::ConstPtr& mg);
        ros::Subscriber cmdVelSb=nh.subscribe<geometry_msgs::Twist>("cmd_vel",10,&Omni::cmdVelCb,this);

        void mtRun(int num,float spd);
};

void Omni::mtRun(int num,float spd){
    std_msgs::Float32 mg;
    mg.data=spd;
    mtPb[num].publish(mg);
}

void Omni::cmdVelCb(const geometry_msgs::Twist::ConstPtr& mg){
    geometry_msgs::Vector3 linear=mg->linear;
    geometry_msgs::Vector3 angular=mg->angular;
    //geometry_msgs::Vector3 angular=mg->angular;
    ROS_INFO("linear  :\nx:%f\ny:%f\nz:%f",linear.x,linear.y,angular.z);
    float x=linear.x;
    float y=linear.y;
    float z=angular.z;
    float v[3];
    v[0]=-x+z;
    v[1]=x/2-sqrt(3)/2*y+z;
    v[2]=x/2+sqrt(3)/2*y+z;
    for(int i=0;i<3;i++)mtRun(i,v[i]);
}

int main(int argc,char**argv){
    ros::init(argc,argv,"omni");
    Omni omni;
    ros::spin();
    return 0;
}
