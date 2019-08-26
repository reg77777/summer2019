#include <ros/ros.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Int16.h>

class Hand{
    public:
        Hand();
        void publish();
    private:
        ros::NodeHandle nh;

        ros::Publisher mtPb=nh.advertise<std_msgs::Float32>("mtHand",1);

        void HandCb(const std_msgs::Float32::ConstPtr& mg);
        ros::Subscriber HandSb=nh.subscribe<std_msgs::Float32>("mtHand",10,&Hand::HandCb,this);

};

Hand::Hand(){
}

void Hand::HandCb(const std_msgs::Float32::ConstPtr& mg){
}

void Hand::publish(){
}

int main(int argc,char**argv){
    ros::init(argc,argv,"hand");
    Hand hand;
    while(ros::ok()){
        hand.publish();
        ros::spinOnce();
    }
    return 0;
}
