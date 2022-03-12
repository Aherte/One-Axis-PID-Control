struct IMU_Values {
  bool Error;
  bool NewDataAvailable;
  unsigned long DeltaTime;
  double YawAngle;
  double PitchAngle;
  double RollAngle;
};

void setup() {
  initializeIMU();
  initializeMotor();
  Serial.begin(115200);
  delay(1000);
}

void loop() {
  struct IMU_Values o = GetIMU_Values();
  if (o.Error) {
    stopMotors();
    resetpid();
    return;
  }
  if (o.NewDataAvailable == false) { return;  }
   
  double controlsignal = getControlSignal(o);
  motorpowers(controlsignal);

}
