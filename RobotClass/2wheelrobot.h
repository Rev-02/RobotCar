class TwoWheelRobot{
protected:
  enum robotstate {
    forwards,
    backwards,
    brake,
    stop,
    turnR,
    turnL,
  };
  robotstate state = stop;
  int leftspeed = 140;
  int rightspeed = 140;
  int targetspeed = 140;
  const MotorEncoder m1;
  const MotorEncoder m2;
  const IrSensor leftSens;
  const IrSensor rightSens;
  bool correcting = true;
  bool measuring;
  unsigned long previousMillis = 0;
  unsigned long currentMillis = 0;
  int speedIncrement = 7;
  int threshold = 3;
  bool lsens = false;
  bool rsens = false;
  bool linefollowing = false;
  bool light = true;
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

  void Right(){
    state = turnR;
    m2.Brake();
    m1.Forwards();
  }

  void Left(){
    state = turnL;
    m1.Brake();
    m2.Forwards();
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

  void updateDistance(){
    if(measuring){
      m1.updateDistance();
      m2.updateDistance();
    }
  }

void moveDistance(bool forwards, int mm){
  if(measuring){
    updateDistance();
  }
  else{
    m1.moveDistance(forwards,mm);
    m2.moveDistance(forwards,mm);
    measuring = true;
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

  bool getLSens(){
    lsens = leftSens.getStatus();
    return lsens;
  }
  bool getRSens(){
    rsens = rightSens.getStatus();
    return rsens;
  }
  void getBothSens(){
    getLSens();
    getRSens();
  }

  void lineFollow( bool light_line){
    light = light_line;
    if (!linefollowing)
    getBothSens();
    if ((lsens != light) && (rsens != light)){
      linefollowing = true;
      Forwards();
      updateLineFollow();
    }
    else{
      updateLineFollow();
    }
  }

  void updateLineFollow(){
    getBothSens();
    if(lsens == light && rsens !=light){
      Left();
    }
    else if(lsens != light && rsens ==light){
      Right();
    }
    else if ((lsens == light) && rsens == light){
      rightspeed = targetspeed;
      leftspeed = targetspeed;
      m1.SetSpeed(leftspeed);
      m2.SetSpeed(rightspeed);
      Forwards();
    }
  }
};
