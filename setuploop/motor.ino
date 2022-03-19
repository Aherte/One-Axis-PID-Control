#include <Servo.h>
Servo right_motor;
Servo left_motor;
#define left_motor_pin 6
#define right_motor_pin 3
#define min_esc_pulse_widht 1000 // min pulse width for esc
#define max_esc_pulse_widht 2000 // max pulse width for esc
#define min_motor_power 0
#define max_motor_power 180
//#define initial_power 25 // to set power in the case that potentiometer is not used

void initializeMotor() {
  right_motor.attach(right_motor_pin, min_esc_pulse_widht, max_esc_pulse_widht);
  left_motor.attach(left_motor_pin, min_esc_pulse_widht, max_esc_pulse_widht);
  stopMotors();
}
void stopMotors() {
  left_motor.write(0);
  right_motor.write(0);
}
void motorpowers(double pidsignal, int pot_value) {
  int  LeftMotorPower = pot_value + pidsignal; // initial_power + pidsignal   in the case that potentiometer is not used
  int  RightMotorPower = pot_value - pidsignal; // initial_power - pidsignal  in the case that potentiometer is not used  

  // limit motor powers for esc
  if (LeftMotorPower < min_motor_power)
    LeftMotorPower = min_motor_power;
  if (LeftMotorPower > max_motor_power)
    LeftMotorPower = max_motor_power;
  if (RightMotorPower < min_motor_power)
    RightMotorPower = min_motor_power;
  if (RightMotorPower > max_motor_power)
    RightMotorPower = max_motor_power;
  ///////////////////////////////////////////////////
 
  if (pot_value <= min_motor_power) { 
    LeftMotorPower = 0;
    RightMotorPower = 0;
  }

  left_motor.write(LeftMotorPower);
  right_motor.write(RightMotorPower);
}
