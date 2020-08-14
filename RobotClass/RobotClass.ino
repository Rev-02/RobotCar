#include "RobotMotors.h"

MotorEncoder motor1(11,12,6,125,2);
MotorEncoder motor2(9,10,5,255,3);

void ISR1(){
  motor1.increaseCount();
}

void ISR2(){
  motor2.increaseCount();
}

void setup(){
Serial.begin(115200);
attachInterrupt(digitalPinToInterrupt(2), ISR1, FALLING);
attachInterrupt(digitalPinToInterrupt(3), ISR2, FALLING);
}


void loop(){
motor1.Forwards();
motor2.Forwards();
motor1.calculateRPM();
motor2.calculateRPM();
Serial.print(motor1.Getrpm());
Serial.print(" , ");
Serial.println(motor2.Getrpm());
delay(10);
}
