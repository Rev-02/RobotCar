#include "RobotMotors.h"
#include "RobotIrSensor.h"
#include "2wheelrobot.h"
MotorEncoder motor1(11,12,6,255,2);
MotorEncoder motor2(9,10,5,255,3);
IrSensor sens1(7);
IrSensor sens2(8);
TwoWheelRobot robo(motor1,motor2,sens1,sens2);

void ISR1(){
  robo.ISR1();
}
void ISR2(){
  robo.ISR2();
}

void setup(){
Serial.begin(115200);
attachInterrupt(digitalPinToInterrupt(2), ISR1, FALLING);
attachInterrupt(digitalPinToInterrupt(3), ISR2, FALLING);
//motor1.moveDistance(true,1000);
//motor2.moveDistance(true,1000);
}


void loop(){
//motor1.Forwards();
//motor2.Forwards();
//motor1.calculateRPM();
//motor2.calculateRPM();
//Serial.print(motor1.Getrpm());
//Serial.print(" , ");
//Serial.println(motor2.getCount());
//motor1.updateDistance();
//motor2.updateDistance();
robo.ForwardsCorrected();
delay(100);
}
