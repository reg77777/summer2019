#include <ros/ros.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Bool.h>
#include <unistd.h>

class Hand{
    public:
        Hand();
    private:
        ros::NodeHandle nh;

        bool state=true;

        ros::Publisher mtPb=nh.advertise<std_msgs::Float32>("mtHand",1);

        void HandCb0(const std_msgs::Bool::ConstPtr& mg);
        ros::Subscriber HandSb0=nh.subscribe<std_msgs::Bool>("cmd_hand0",10,&Hand::HandCb0,this);

        void HandCb1(const std_msgs::Bool::ConstPtr& mg);
        ros::Subscriber HandSb1=nh.subscribe<std_msgs::Bool>("cmd_hand1",10,&Hand::HandCb1,this);

        void ChangeCb(const std_msgs::Bool::ConstPtr& mg);
        ros::Subscriber bt2Sb=nh.subscribe<std_msgs::Bool>("bt2",10,&Hand::ChangeCb,this);

        float handlag0;
        float handlag1;

};

Hand::Hand(){
    nh.param<float>("handlag0",handlag0,0.5);
    nh.param<float>("handlag1",handlag1,0.5);
}

void Hand::HandCb0(const std_msgs::Bool::ConstPtr& mg){
    if(state&&!mg->data){
        std_msgs::Float32 m;
        m.data=200;
        mtPb.publish(m);
        sleep(handlag0);
        m.data=0;
        mtPb.publish(m);
    }
    if(!state&&mg->data){
        std_msgs::Float32 m;
        m.data=-200;
        mtPb.publish(m);
        sleep(handlag0);
        m.data=0;
        mtPb.publish(m);
    }
    state=mg->data;
}

void Hand::HandCb1(const std_msgs::Bool::ConstPtr& mg){
    if(state&&!mg->data){
        std_msgs::Float32 m;
        m.data=200;
        mtPb.publish(m);
        sleep(handlag1);
        m.data=0;
        mtPb.publish(m);
    }
    if(!state&&mg->data){
        std_msgs::Float32 m;
        m.data=-200;
        mtPb.publish(m);
        sleep(handlag1);
        m.data=0;
        mtPb.publish(m);
    }
    state=mg->data;
}

void Hand::ChangeCb(const std_msgs::Bool::ConstPtr& mg){
    if(mg->data){
        ros::Rate rate(1);
        if(!state){
            std_msgs::Float32 m;
            m.data=150;
            mtPb.publish(m);
            rate.sleep();
            m.data=0;
            mtPb.publish(m);
        }
        else{
            std_msgs::Float32 m;
            m.data=-150;
            mtPb.publish(m);
            rate.sleep();
            m.data=0;
            mtPb.publish(m);
        }
        state=state;
        rate.sleep();
    }
}

int main(int argc,char**argv){
    ros::init(argc,argv,"hand");
    Hand hand;
    ros::spin();
    return 0;
}
