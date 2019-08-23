#include <Wire.h>
#include <SparkFunLSM9DS1.h>

#define USE_USBCON

#define LSM9DS1_M 0x1E
#define LSM9DS1_AG 0x6B

LSM9DS1 imu;
#define PRINT_SPEED 250
static unsigned long lastPrint=0;
#define DECLINATION -0.74

void setup(){
  Serial.begin(115200);
  imu.settings.device.commInterface=IMU_MODE_I2C;
  imu.settings.device.mAddress=LSM9DS1_M;
  imu.settings.device.agAddress=LSM9DS1_AG;
  if(!imu.begin()){
    Serial.println("AAAAAAA");
    while(1);
  }
}

void loop(){
  if(imu.gyroAvailable())imu.readGyro();
  if(imu.accelAvailable())imu.readAccel();
  if(imu.magAvailable())imu.readMag();
  if((lastPrint+PRINT_SPEED)<millis()){
    printGyro();
    printAccel();
    printMag();
    printAttitude(imu.ax,imu.ay,imu.az,-imu.my,-imu.mx,imu.mz);
    Serial.println();
    lastPrint=millis();
  }
}

void printGyro(){
  Serial.print("G: ");
  Serial.print(imu.calcGyro(imu.gx),2);
  Serial.print(", ");
  Serial.print(imu.calcGyro(imu.gy),2);
  Serial.print(", ");
  Serial.print(imu.calcGyro(imu.gz),2);
  Serial.println("deg/s");
  Serial.print(imu.gx);
  Serial.print(", ");
  Serial.print(imu.gy);
  Serial.print(", ");
  Serial.println(imu.gz);
}



void printAccel(){
 Serial.print("A: ");
 Serial.print(imu.calcAccel(imu.ax), 2);
 Serial.print(", ");
 Serial.print(imu.calcAccel(imu.ay), 2);
 Serial.print(", ");
 Serial.print(imu.calcAccel(imu.az), 2);
 Serial.println(" g");
 Serial.print(imu.ax);
 Serial.print(", ");
 Serial.print(imu.ay);
 Serial.print(", ");
 Serial.println(imu.az);
}


void printMag(){
 Serial.print("M: ");
 Serial.print(imu.calcMag(imu.mx), 2);
 Serial.print(", ");
 Serial.print(imu.calcMag(imu.my), 2);
 Serial.print(", ");
 Serial.print(imu.calcMag(imu.mz), 2);
 Serial.println(" gauss");
 Serial.print(imu.mx);
 Serial.print(", ");
 Serial.print(imu.my);
 Serial.print(", ");
 Serial.println(imu.mz);
}
