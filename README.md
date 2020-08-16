# RobotCar
An Arduino controlled robot car with wheel encoders, line following, and distance detection.
## Parts
- Arduino Uno R3
- Generic Robot motors and chassis
- 4 cell battery holder for motors
- 9v battery for Arduino
- l298N motor driver
- IR tachometer sensors
- IR line LED and photodiode pair
- HCSR04

---
For pinout see *pinout.md*
---
To access the rotary encoders, an ISR needs to be made within the sketch, and assigned to each instance on setup using the attach_Interupt method. see this example:
```
MotorEncoder motor1(11,12,6,255,2);
void ISR1(){
  motor1.increaseCount();
}
void setup(){
attachInterrupt(digitalPinToInterrupt(2), ISR1, FALLING);
}
```
