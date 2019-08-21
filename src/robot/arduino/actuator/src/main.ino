#include "motor/motor.hpp"
#include "encoder/encoder.hpp"
#include <ros.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Int32.h>

Motor mt0(2,3);
Motor mt1(4,5);
Motor mt2(6,7);
Encoders encs;

//define NodeHandle
ros::NodeHandle nh;

//define Callbacks
void mt0Cb(const std_msgs::Float32 &Mg){
    mt0.run(Mg.data);
}
void mt1Cb(const std_msgs::Float32 &Mg){
    mt1.run(Mg.data);
}
void mt2Cb(const std_msgs::Float32 &Mg){
    mt2.run(Mg.data);
}

//define Subscribers
ros::Subscriber<std_msgs::Float32>mt0Sb("mt0",&mt0Cb);
ros::Subscriber<std_msgs::Float32>mt1Sb("mt1",&mt1Cb);
ros::Subscriber<std_msgs::Float32>mt2Sb("mt2",&mt2Cb);

//defien msg
std_msgs::Int32 enc0Mg;
std_msgs::Int32 enc1Mg;
std_msgs::Int32 enc2Mg;

//define Publisher
ros::Publisher enc0Pb("enc0",&enc0Mg);
ros::Publisher enc1Pb("enc1",&enc1Mg);
ros::Publisher enc2Pb("enc2",&enc2Mg);

void setup(){
    nh.initNode();
    //set subscriber
    nh.subscribe(mt0Sb);
    nh.subscribe(mt1Sb);
    nh.subscribe(mt2Sb);
    //set pubulisher
    nh.advertise(enc0Pb);
    nh.advertise(enc1Pb);
    nh.advertise(enc2Pb);
}

void loop(){
    //publish
    enc0Mg.data=encs.counts[0];
    enc0Pb.publish(&enc0Mg);
    nh.spinOnce();
    enc1Mg.data=encs.counts[1];
    enc1Pb.publish(&enc1Mg);
    nh.spinOnce();
    enc2Mg.data=encs.counts[2];
    enc2Pb.publish(&enc2Mg);
    nh.spinOnce();
}
