# One-Axis-PID-Control

To use PID controller, there must be a feedback and close loop system, in this project the feedback comes from the mpu6050 3-axis gyro module and ı used atmega328P better known as arduino to process data and create a close loop. Also, ı used 2 brushless motors (EMAX XA2212 1400KV) and to use them with pwm signals, ı used 2 electronic speed controllers(ESC 40 A). For the main power source ı used 2200 mAh 3 cells li-po battery (you can use another powersupply because batteries run out fast). to actualize this project of course a seesaw system needed.I printed seesaw system from 3d printer but ı recommend to use material other than plastic because when ı try to adjust fixed pid variables, ı almost 10 times broke the system.

## Description of PID values in PID control

* P (proportional) accounts for present values of the error. For example, if the error is large and positive, the control output will also be large and positive.

* I (integral) accounts for all past values of the error. For example, if the current output is not sufficiently strong, the integral of the error will accumulate over time, and the controller will respond by applying a stronger action.

* D (differential) accounts for possible future trends of the error, based on its current rate of change.
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
* Arduino can freezes because i2c communication timeout did not defined by default in Wire library which is a core library of Arduino. So, we have to set timeout variables with manually or in the code. I prefered to do it manually with changing timeout variables of the Wire library.

  
## MPU 6050 Connections
![image](https://user-images.githubusercontent.com/55800601/159141126-01f0b7cb-250f-4395-9bc5-6a82780e0657.png)

![giphy](https://user-images.githubusercontent.com/55800601/159183971-532ffe2c-9aaa-44e9-a01d-d124bd19affa.gif)

## TO REACH YOUTUBE VİDEO
https://youtu.be/R3X3auJVGYw
