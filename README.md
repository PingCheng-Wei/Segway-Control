# Segway-Control ( TM4C123G Launch Pad, C++)
This is an internship project at KIT university with the following main purpose:

* Practicing object-oriented programming &rarr; C++
* Understanding register
* Knowing how to program microcontroller
* Controlling Segway with the following function parts:
  * General Purpose Input/Output: GPIO class
  * Timer: Timer class
  * Analog-to-Digital Converter: ADC class
  * Pulse-Width Modulation: PWM class
  * Segway Balancing Control: Balancing Class


**Overall test setup:**
![Overall_test_setup](https://user-images.githubusercontent.com/63096297/138184679-d918ad87-f123-4692-9914-ed213fd24f4a.jpg)


**Playing around with Segway !!! :)**

![Segway_test](https://user-images.githubusercontent.com/63096297/138235190-eb8ff633-9cdd-4b5c-b2b2-1957eccfa3c2.gif)


## The following is the simulation test results

#### Using Timer class to control the blinking speed of the LED, indicating that the Timer class is successful.

![Timer1](https://user-images.githubusercontent.com/63096297/138235217-5c421430-f81f-49d8-aa7b-c57d91a96c01.gif)
![Timer2](https://user-images.githubusercontent.com/63096297/138236988-8191cae4-b304-4a68-a055-044b491a2ccc.gif)

#### We assigned the different voltage ranges to different LED colors. Thus, by varying the value of potentiometer, which corresponds to different measured voltage by ADC in microcontroller, we see it has different light on, indicating that the ADC class is successful.

![adc](https://user-images.githubusercontent.com/63096297/138234997-993bde5c-3783-4107-ae58-32706822783a.gif)

#### Successfully given 100% duty cycle to turn the motors forward in full power with PWM signal, indicating that the PWM class is successful

![PWM_full_power](https://user-images.githubusercontent.com/63096297/138235178-7d9eb4dd-be7b-4157-af18-00fc9a4718e4.gif)


### Enable balance control with the help of [MPU-6050 module integrates a 3-axis acceleration sensor and a 3-axis gyroscope](https://www.reichelt.de/de/en/developer-boards-acceleration-amp-gyroscope-3-axis-mpu-605-debo-sens-3axis-p253987.html?GROUPID=9008&START=0&OFFSET=16&SID=942f58b2b0704a274b9279a173fd25e8157a33d9db80fe39ac420&LANGUAGE=EN&&r=1)

#### Successfully control the motors to accelerate and decelerate in both directions, indicating that in real-world Segway test we could move forward and backwork saftely

![motor_change_direction](https://user-images.githubusercontent.com/63096297/138235078-cc7530c8-9a4d-4056-b6ea-e13d4d087d56.gif)


#### Successfully control the motors to be able to turn in different speed, indicating that in real-world Segway test we could not only move forward and backwork in a straight line but also turn left and right in both direction

![Segway_Turning](https://user-images.githubusercontent.com/63096297/138236901-5b6463d5-a3a4-4e85-9289-2fd694def320.gif)


