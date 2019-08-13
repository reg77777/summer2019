#include <ros/ros.h>
#include <std_msgs/String.h>
#include <iostream>

int main(int argc,char**argv){
    ros::init(argc,argv,"omni");
    ros::NodeHandle nh;
    ros::Publisher pub=nh.advertise<std_msgs::String>("chatter",1000);
    ros::Rate loop_rate(1);
    std_msgs::String msg;
    while(ros::ok()){
        msg.data="hello world";
        pub.publish(msg);
        ros::spinOnce();
        loop_rate.sleep();
        std::cout<<msg.data<<std::endl;
    }
}

