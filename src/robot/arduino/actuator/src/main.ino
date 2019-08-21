#include "motor/motor.hpp"
#include "encoder/encoder.hpp"
#include <ros.h>

Encoders encs;
Motor mt0(2,3);
Motor mt1(4,5);
Motor mt2(6,7);

//define NodeHandle
ros::NodeHandle nh;

//define Callbacks
void mt0Cb(const std_msgs::Float32 &msg){
    mt0.run(msg.data);
}
void mt1Cb(const std_msgs::Float32 &msg){
    mt1.run(msg.data);
}
void mt2Cb(const std_msgs::Float32 &msg){
    mt2.run(msg.data);
}

//define Subscribers
ros::Subscriber<std_msgs::Float32>mt0Sb("mt0");
ros::Subscriber<std_msgs::Float32>mt1Sb("mt1");
ros::Subscriber<std_msgs::Float32>mt2Sb("mt2");

//defien msg
std_msgs::Int32 enc0Mg;
std_msgs::Int32 enc1Mg;
std_msgs::Int32 enc2Mg;

//define Publisher
ros::Publisher enc0Pb("enc0",&enc0Mg);
ros::Publisher enc1Pb("enc1",&enc1Mg);
ros::Publisher enc2Pb("enc2",&enc2Mg);

void setup(){
    nh.init();
    //set subscriber
    nh.subscribe(mt0Sb);
    nh.subscribe(mt1Sb);
    nh.subscribe(mt2Sb);
}

void loop(){
    //publish
    enc0Mg.data=encs.counts[0];
    nh.advertise(enc0Pb);
    nh.spinOnce();
    enc1Mg.data=encs.counts[1];
    nh.advertise(enc1Pb);
    nh.spinOnce();
    enc2Mg.data=encs.counts[2];
    nh.advertise(enc2Pb);
    nh.spinOnce();
}
