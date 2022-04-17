#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif
MPU6050 mpu;
#define INTERRUPT_PIN 2
#define IMU_COMMUNICATION_TIMEOUT 200

// initial point calibration
#define ACCEL_OFFSET_X -531
#define ACCEL_OFFSET_Y 521
#define ACCEL_OFFSET_Z 384
#define GYRO_OFFSET_X 147
#define GYRO_OFFSET_Y 288
#define GYRO_OFFSET_Z -10
///////////////////////////////////

bool dmpReady = false;
uint8_t mpuIntStatus;
uint8_t devStatus;
uint16_t packetSize;
uint16_t fifoCount;
uint8_t fifoBuffer[64];

Quaternion q;
VectorInt16 aa;
VectorInt16 aaReal;
VectorInt16 aaWorld;
VectorFloat gravity;
float euler[3];
float ypr[3];
volatile bool mpuInterrupt = false;
void dmpDataReady() {
  mpuInterrupt = true;
}

unsigned long last_time = 0;

void initializeIMU() {
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  Wire.begin(100);
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
  Fastwire::setup(100, true);
#endif

  mpu.initialize();
  pinMode(INTERRUPT_PIN, INPUT);

  if (!mpu.testConnection()) {
    Serial.println("*imu test connection failed!");
  }
  devStatus = mpu.dmpInitialize();

  mpu.setXGyroOffset(GYRO_OFFSET_X);
  mpu.setYGyroOffset(GYRO_OFFSET_Y);
  mpu.setZGyroOffset(GYRO_OFFSET_Z);
  mpu.setXAccelOffset(ACCEL_OFFSET_X); 
  mpu.setYAccelOffset(ACCEL_OFFSET_Y);
  mpu.setZAccelOffset(ACCEL_OFFSET_Z);

  if (devStatus == 0) {
    mpu.setDMPEnabled(true);
    attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), dmpDataReady, RISING);
    mpuIntStatus = mpu.getIntStatus();
    dmpReady = true;
    packetSize = mpu.dmpGetFIFOPacketSize();
  }
}

struct IMU_Values GetIMU_Values() {
  struct IMU_Values o;
  o.NewDataAvailable = false;
  if (!dmpReady)
    return o;

  unsigned long current_time = millis();
  unsigned long delta_time = current_time - last_time;

  if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer)) {

    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

    o.YawAngle = ypr[0] * 180 / M_PI; // in my case just the roll angle is enough 
    o.RollAngle = ypr[1] * 180 / M_PI ; // but ı prefered to read yaw and pitch angles too if ı want to develop the project for other axises
    o.PitchAngle = ypr[2] * 180 / M_PI;  // 180 / M_PI to convert radian to degree
    o.NewDataAvailable = true;
    o.DeltaTime = delta_time;

    if (last_time == 0) {
      last_time = current_time;
      o.Error = true;
      return o;
    }
    last_time = current_time;
  }

  if (delta_time > IMU_COMMUNICATION_TIMEOUT)
    o.Error = true;
  else
    o.Error = false;

  return o;
}
