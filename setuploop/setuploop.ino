#define pot_Pin A0

struct IMU_Values {
  bool Error;
  bool NewDataAvailable;
  unsigned long DeltaTime;
  double YawAngle;
  double PitchAngle;
  double RollAngle;
};

uint16_t pot_value = 0;

void setup() {
  initializeIMU();
  initializeMotor();
}

void loop() {
  struct IMU_Values o = GetIMU_Values();
  if (o.Error) {
    stopMotors();
    resetpid();
    return;
  }
  if (o.NewDataAvailable == false) // checking newdata because arduino is faster than imu.
    return;

  pot_value = analogRead(pot_Pin);  // reading data from potentiometer to set power. 
  pot_value = map(pot_value, 0, 1023, 0, 180); 

  double controlsignal = getControlSignal(o); 

  motorpowers(controlsignal, pot_value);

}
