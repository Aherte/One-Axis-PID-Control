#include <Servo.h>
Servo right_motor;
Servo left_motor;
#define initial_power 40

void initializeMotor() {
  right_motor.attach(3, 1000, 2000);
  left_motor.attach(5, 1000, 2000);
  stopMotors();
}
void stopMotors() {
  left_motor.write(0);
  right_motor.write(0);
}
void motorpowers(double pidsignal) {
  int  LeftMotorPower = initial_power + pidsignal;
  int  RightMotorPower = initial_power - pidsignal;
  if (LeftMotorPower < 0)
    LeftMotorPower = 0;
  if (LeftMotorPower > 180) 
    LeftMotorPower = 180;
  if (RightMotorPower < 0)
    RightMotorPower = 0;
  if (RightMotorPower > 180)
    RightMotorPower = 180;
   /*
    Serial.print("LeftMotorPower:");
    Serial.print(LeftMotorPower);
    Serial.print(", ");

    Serial.print("RightMotorPower:");
    Serial.print(RightMotorPower);
    Serial.print(", ");
    Serial.println();
   */ 
  left_motor.write(LeftMotorPower);
  right_motor.write(RightMotorPower);
}
