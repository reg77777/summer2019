#include <ros/ros.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Bool.h>
#include <unistd.h>

class Arm{
    public:
        Arm();
    private:
        ros::NodeHandle nh;

        ros::Publisher mtPb=nh.advertise<std_msgs::Float32>("mtArm",1);

        void ArmCb0(const std_msgs::Bool::ConstPtr& mg);
        ros::Subscriber ArmSb0=nh.subscribe<std_msgs::Bool>("cmd_arm0",10,&Arm::ArmCb0,this);

        void ArmCb1(const std_msgs::Bool::ConstPtr& mg);
        ros::Subscriber ArmSb1=nh.subscribe<std_msgs::Bool>("cmd_arm1",10,&Arm::ArmCb1,this);


        bool up=true;
        float armlag0,armlag1;
};

Arm::Arm(){
    nh.param<float>("armlag0",armlag0,1);
    nh.param<float>("armlag1",armlag1,1);
}

void Arm::ArmCb0(const std_msgs::Bool::ConstPtr& mg){
    std_msgs::Float32 m;
    if(mg->data&&!up){
        m.data=-80;
        mtPb.publish(m);
        sleep(armlag0);
    }
    else if(!mg->data&&up){
        ros::Rate rate(armlag0);
        m.data=80;
        mtPb.publish(m);
        sleep(armlag0);
    }
    m.data=0;
    mtPb.publish(m);
    up=mg->data;
}

void Arm::ArmCb1(const std_msgs::Bool::ConstPtr& mg){
    std_msgs::Float32 m;
    if(mg->data&&!up){
        m.data=-80;
        mtPb.publish(m);
        sleep(armlag1);
    }
    else if(!mg->data&&up){
        m.data=80;
        mtPb.publish(m);
        sleep(armlag1);
    }
    m.data=0;
    mtPb.publish(m);
    up=mg->data;
}


int main(int argc,char**argv){
    ros::init(argc,argv,"arm");
    Arm arm;
    ros::spin();
    return 0;
}
