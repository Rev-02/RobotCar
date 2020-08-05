#include "RobotMotors.h"

MotorEncoder motor1(11,12,3,255,2);

void setup(){
Serial.begin(115200);
}
void loop(){
motor1.Forwards();
Serial.println(motor1.getCount());
delay(10);
}
