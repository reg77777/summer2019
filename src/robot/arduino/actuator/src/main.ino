#include "motor/motor.hpp"
#include "encoder/encoder.hpp"
#include <ros.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Bool.h>

Motor mt0(8,9);
Motor mt1(4,5);
Motor mt2(6,7);
Motor mtArm(10,11);
Motor mtHand(12,46);
Encoders encs;
int btS=30;
int btC=31;

//define NodeHandle
ros::NodeHandle nh;

//define Callbacks
void mt0Cb(const std_msgs::Float32 &mg){
    mt0.run(mg.data);
}
void mt1Cb(const std_msgs::Float32 &mg){
    mt1.run(mg.data);
}
void mt2Cb(const std_msgs::Float32 &mg){
    mt2.run(mg.data);
}
void mtArmCb(const std_msgs::Float32 &mg){
    mtArm.run(mg.data);
}
void mtHandCb(const std_msgs::Float32 &mg){
    mtHand.run(mg.data);
}
void encResetCb(const std_msgs::Int16 &mg){
    encs.reset(mg.data);
}

//define Subscribers
ros::Subscriber<std_msgs::Float32>mt0Sb("mt0",&mt0Cb);
ros::Subscriber<std_msgs::Float32>mt1Sb("mt1",&mt1Cb);
ros::Subscriber<std_msgs::Float32>mt2Sb("mt2",&mt2Cb);
ros::Subscriber<std_msgs::Float32>mtArmSb("mtArm",&mtArmCb);
ros::Subscriber<std_msgs::Float32>mtHandSb("mtHand",&mtHandCb);
ros::Subscriber<std_msgs::Int16>encResetSb("encReset",&encResetCb);

//defien msg
std_msgs::Int32 enc0Mg;
std_msgs::Int32 enc1Mg;
std_msgs::Int32 enc2Mg;
std_msgs::Int32 enc3Mg;
std_msgs::Bool btSMg;
std_msgs::Bool btCMg;

//define Publisher
ros::Publisher enc0Pb("enc0",&enc0Mg);
ros::Publisher enc1Pb("enc1",&enc1Mg);
ros::Publisher enc2Pb("enc2",&enc2Mg);
ros::Publisher enc3Pb("enc3",&enc3Mg);
ros::Publisher btSPb("btS",&btSMg);
ros::Publisher btCPb("btC",&btCMg);

void setup(){
    nh.initNode();
    //set pin
    pinMode(btS,INPUT_PULLUP);
    pinMode(btC,INPUT_PULLUP);
    //set subscriber
    nh.subscribe(mt0Sb);
    nh.subscribe(mt1Sb);
    nh.subscribe(mt2Sb);
    nh.subscribe(mtArmSb);
    nh.subscribe(mtHandSb);
    nh.subscribe(encResetSb);
    //set pubulisher
    nh.advertise(enc0Pb);
    nh.advertise(enc1Pb);
    nh.advertise(enc2Pb);
    nh.advertise(enc3Pb);
    nh.advertise(btSPb);
    nh.advertise(btCPb);
}

void loop(){
    //publish
    enc0Mg.data=encs.counts[0]; enc0Pb.publish(&enc0Mg);
    nh.spinOnce();
    delay(5);

    enc1Mg.data=encs.counts[1]; enc1Pb.publish(&enc1Mg);
    nh.spinOnce();
    delay(5);

    enc2Mg.data=encs.counts[2]; enc2Pb.publish(&enc2Mg);
    nh.spinOnce();
    delay(5);

    enc3Mg.data=encs.counts[3]; enc3Pb.publish(&enc3Mg);
    nh.spinOnce();
    delay(5);

    btSMg.data=digitalRead(btS); btSPb.publish(&btSMg);
    nh.spinOnce();
    delay(5);

    btCMg.data=digitalRead(btC); btCPb.publish(&btCMg);
    nh.spinOnce();
    delay(5);
}
