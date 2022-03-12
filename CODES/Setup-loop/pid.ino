#define Kp 3.55
#define Ki 0.005
#define Kd 2.05
double pid_i, last_error;

void resetpid() {
  pid_i = 0; last_error = 0;
}
double getControlSignal(struct IMU_Values imu) {
  double error = imu.RollAngle;

  double pid_p = Kp * error;
  double pid_d = Kd * ((error - last_error) / imu.DeltaTime);

  if ( error < 3 && error > -3)
    pid_i = pid_i + (error * Ki) ;  

  double control_signal = pid_i + pid_d + pid_p;
  /*
  Serial.print("error:");
  Serial.print(error);
  Serial.print(",");
  Serial.print("pid_i:");
  Serial.print(pid_i);
  Serial.print(",");
  Serial.print("control_signal:");
  Serial.print(control_signal);
  Serial.print(", ");
  */
  last_error = error;

  return control_signal;
}
