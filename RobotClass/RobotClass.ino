#include "RobotMotors.h"

MotorEncoder motor1(11,12,6,120,2);
MotorEncoder motor2(9,10,5,120,3);

void ISR1(){
  motor1.increaseCount();
}

void ISR2(){
  motor2.increaseCount();
}

void setup(){
Serial.begin(115200);
attachInterrupt(digitalPinToInterrupt(2), ISR1, RISING);
attachInterrupt(digitalPinToInterrupt(3), ISR2, RISING);
}


void loop(){
motor1.Forwards();
motor2.Forwards();
Serial.print(motor1.getCount());
Serial.print(" , ");
Serial.println(motor2.getCount());
motor1.calculateRPM();
Serial.println(motor1.Getrpm());
delay(10);
}
