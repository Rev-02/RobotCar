class TwoWheelRobot{
protected:
  const MotorEncoder m1;
  const MotorEncoder m2;
  const IrSensor leftSens;
  const IrSensor rightSens;
public:
  TwoWheelRobot(const MotorEncoder &M1,const MotorEncoder &M2,const IrSensor &l_s_pin,const IrSensor &r_s_pin): m1(M1),m2(M2),leftSens(l_s_pin),rightSens(r_s_pin){  }

};
