#include <SPI.h>
#include <Wire.h>
#include <SparkFunLSM9DS1.h>

#include <ros.h>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/MagneticField.h>

#define USE_USBCON

ros::NodeHandle nh;
sensor_msgs::Imu imumsg;
sensor_msgs::MagneticField mag;
ros::Publisher imuPb("imu/data_raw",&imumsg);
ros::Publisher magPb("imu/mag",&mag);

#define LSM9DS1_M 0x1E
#define LSM9DS1_AG 0x6B

LSM9DS1 imu;
#define PRINT_SPEED 250
static unsigned long lastPrint=0;
#define DECLINATION -0.74

void setup(){
    imu.settings.device.commInterface=IMU_MODE_I2C;
    imu.settings.device.mAddress=LSM9DS1_M;
    imu.settings.device.agAddress=LSM9DS1_AG;
    if(!imu.begin()){
        nh.loginfo("AAAAAAA");
        while(1);
    }
    delay(1000);
    nh.initNode();
}

void loop(){
    if(imu.gyroAvailable())imu.readGyro();
    if(imu.accelAvailable())imu.readAccel();
    if(imu.magAvailable())imu.readMag();
    if((lastPrint+PRINT_SPEED)<millis()){
        printGyro();
        printAccel();
        printMag();
        lastPrint=millis();
    }
    nh.spinOnce();
}

void printGyro(){
    nh.loginfo("G");
    /*
    nh.loginfo(imu.calcGyro(imu.gx),2);
    nh.loginfo(imu.calcGyro(imu.gy),2);
    nh.loginfo(imu.calcGyro(imu.gz),2);
    */
}

void printAccel(){
    nh.loginfo("A");
    /*
    nh.loginfo(imu.calcAccel(imu.ax), 2);
    nh.loginfo(imu.calcAccel(imu.ay), 2);
    nh.loginfo(imu.calcAccel(imu.az), 2);
    */
}


void printMag(){
    nh.loginfo("M");
    /*
    nh.loginfo(imu.calcMag(imu.mx), 2);
    nh.loginfo(imu.calcMag(imu.my), 2);
    nh.loginfo(imu.calcMag(imu.mz), 2);
    */
}


/*
#include <Wire.h>
#include <SparkFunLSM9DS1.h>

#include <ros.h>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/MagneticField.h>

ros::NodeHandle nh;
sensor_msgs::Imu imumsg;
sensor_msgs::MagneticField mag;
ros::Publisher imuPb("imu/data_raw",&imumsg);
ros::Publisher magPb("imu/mag",&mag);

#define LSM9DS1_M 0x1E
#define LSM9DS1_AG 0x6B

LSM9DS1 imu;
#define PRINT_SPEED 250
#define DECLINATION -0.74

void setup(){
    imu.settings.device.commInterface=IMU_MODE_I2C;
    imu.settings.device.mAddress=LSM9DS1_M;
    imu.settings.device.agAddress=LSM9DS1_AG;
    if(!imu.begin()){
        while(1);
    }
    nh.initNode();
    nh.advertise(imuPb);
    nh.advertise(magPb);
}

void loop(){
    if(imu.gyroAvailable())imu.readGyro();
    if(imu.accelAvailable())imu.readAccel();
    if(imu.magAvailable())imu.readMag();
    float aX,aY,aZ,gX,gY,gZ,mX,mY,mZ;
    aX=imu.calcAccel(imu.ax);
    aY=imu.calcAccel(imu.ay);
    aZ=imu.calcAccel(imu.az);
    gX=imu.calcGyro(imu.gx);
    gY=imu.calcGyro(imu.gy);
    gZ=imu.calcGyro(imu.gz);
    mX=imu.calcMag(imu.mx);
    mY=imu.calcMag(imu.my);
    mZ=imu.calcMag(imu.mz);
    Serial.print(aX);
    Serial.print(" ");
    Serial.print(aY);
    Serial.print(" ");
    Serial.println(aZ);
    delay(1000);

    imumsg.header.frame_id="imu_link";
    imumsg.header.stamp=nh.now();
    imumsg.angular_velocity.x=gX;
    imumsg.angular_velocity.y=gY;
    imumsg.angular_velocity.z=gZ;
    imumsg.linear_acceleration.x=aX;
    imumsg.linear_acceleration.y=aY;
    imumsg.linear_acceleration.z=aZ;
    imuPb.publish(&imumsg);

    nh.spinOnce();
    delay(500);

    mag.header.frame_id="imu_link";
    mag.header.stamp=nh.now();
    mag.magnetic_field.x=mX;
    mag.magnetic_field.y=mY;
    mag.magnetic_field.z=mZ;
    magPb.publish(&mag);

    nh.spinOnce();
    delay(500);

}
*/
