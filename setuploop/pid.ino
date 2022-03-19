#define Kp 0.3  
#define Ki 0.0004    // these fixed pid variables can be adjusted different values. In my case these values worked fine 
#define Kd 110  

double pid_i, last_error;

void resetpid() {
  pid_i = 0; last_error = 0;
}
double getControlSignal(struct IMU_Values imu) {
  double error = imu.RollAngle; 

  double pid_p = error; 
  double pid_d = (error - last_error) / imu.DeltaTime; //error change in elapsed time = derivative

  //if ( error < 5 && error > -5) //integral variable can be used if error is lower. 
  pid_i = pid_i + (error * imu.DeltaTime) ; // increase integral term over time to minimize the error = integral

  double control_signal = (Ki*pid_i) + (Kd*pid_d) + (Kp*pid_p);

  last_error = error;

  return control_signal;
}
