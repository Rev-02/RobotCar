class TwoWheelRobot{
protected:
  enum robotstate {
    forwards,
    backwards,
    brake,
    stop,
    turnC,
    turnAC,
  };
  robotstate state = stop;
  int leftspeed = 210;
  int rightspeed = 210;
  int targetspeed = 210;
  const MotorEncoder m1;
  const MotorEncoder m2;
  const IrSensor leftSens;
  const IrSensor rightSens;
  bool correcting = true;
  unsigned long previousMillis = 0;
  unsigned long currentMillis = 0;
  int speedIncrement = 7;
  int threshold = 3;
public:
  TwoWheelRobot(const MotorEncoder &m1,const MotorEncoder &m2,const IrSensor &l_s_pin,const IrSensor &r_s_pin): m1(m1),m2(m2),leftSens(l_s_pin),rightSens(r_s_pin){
    m1.SetSpeed(leftspeed);
    m2.SetSpeed(rightspeed);
  }

 void ISR1(){
    m1.increaseCount();
  }

 void ISR2(){
    m2.increaseCount();
  }
  void Forwards(){
    if(state != forwards){
      state = forwards;
      m1.SetSpeed(leftspeed);
      m2.SetSpeed(rightspeed);
      m1.Forwards();
      m2.Forwards();
    }
  }
  void Backwards(){
    if(state != backwards){
      state = backwards;
      m1.SetSpeed(leftspeed);
      m2.SetSpeed(rightspeed);
      m1.Backwards();
      m2.Backwards();
    }
  }
  void Brake(){
    state = brake;
    m1.Brake();
    m2.Brake();
    correcting = false;
  }
  void Stop(){
    state = stop;
    m1.Stop();
    m2.Stop();
    correcting = false;
  }

  void ForwardsCorrected(){
    if(correcting && state == forwards){
      updateCorrection();
    }
    else{
      correcting = true;
      Forwards();
    }
  }
  void BackwardsCorrected(){
    if(correcting && state == backwards){
      updateCorrection();
    }
    else{
      correcting = true;
      Backwards();
    }
  }

  void updateCorrection(){
    if(correcting){
      m1.calculateRPM();
      m2.calculateRPM();
      if(m1.Getrpm() - m2.Getrpm() > threshold){
        if (leftspeed - speedIncrement > 0){
        leftspeed -= speedIncrement;
        m1.SetSpeed(leftspeed);
        }
        if (rightspeed + speedIncrement < targetspeed){
        rightspeed += speedIncrement;
        m2.SetSpeed(rightspeed);
        }

    }
    else if(m2.Getrpm() - m1.Getrpm() > threshold){
        if (rightspeed - speedIncrement > 0){
        rightspeed -= speedIncrement;
        m2.SetSpeed(rightspeed);
        }
        if (leftspeed + speedIncrement < targetspeed){
        leftspeed += speedIncrement;
        m1.SetSpeed(leftspeed);
        }

    }
    else{
      if (rightspeed + speedIncrement < targetspeed){
        rightspeed += speedIncrement;
      }
      else{
        rightspeed = targetspeed;
      }
      if (leftspeed + speedIncrement < targetspeed){
        leftspeed += speedIncrement;
      }
      else{
        leftspeed = targetspeed;
      }
      m1.SetSpeed(leftspeed);
      m2.SetSpeed(rightspeed);
    }
  }
  }
};
