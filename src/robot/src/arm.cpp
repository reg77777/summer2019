#include <ros/ros.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Int32.h>

class Arm{
    public:
        Arm();
        void publish();
    private:
        ros::NodeHandle nh;

        ros::Publisher mtPb=nh.advertise<std_msgs::Float32>("mtArm",1);

        void e3Cb(const std_msgs::Int32::ConstPtr& mg);
        ros::Subscriber e3Sb=nh.subscribe<std_msgs::Int32>("enc3",10,&Arm::e3Cb,this);

        void ArmCb(const std_msgs::Float32::ConstPtr& mg);
        ros::Subscriber ArmSb=nh.subscribe<std_msgs::Float32>("mtArm",10,&Arm::ArmCb,this);

        long long int e3c=0;
        long long int x=0;
        float armkp;
};

Arm::Arm(){
    nh.param<float>("armkp",armkp,0.1);
}

void Arm::e3Cb(const std_msgs::Int32::ConstPtr& mg){
    e3c=mg->data;
}

void Arm::ArmCb(const std_msgs::Float32::ConstPtr& mg){
    x=mg->data;
}

void Arm::publish(){
    std_msgs::Float32 mg;
    mg.data=armkp*(x-e3c);
    mtPb.publish(mg);
}

int main(int argc,char**argv){
    ros::init(argc,argv,"arm");
    Arm arm;
    ros::Rate loop_rate(5);
    while(ros::ok()){
        arm.publish();
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}
