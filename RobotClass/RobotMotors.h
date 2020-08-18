class Motor
{
protected:
  int forwardsPin;
  int backwardsPin;
  int enablePin;
  enum state {
    forwards,
    backwards,
    brake,
    stop
  };
  state motorState = stop;
public:
  Motor(int fwdpin, int bckpin, int enapin) : forwardsPin(fwdpin),backwardsPin(bckpin),enablePin(enapin){
    pinMode(forwardsPin, OUTPUT);
    pinMode(backwardsPin, OUTPUT);
    pinMode(enablePin, OUTPUT);
  }

  void Stop(){
    if (motorState != stop){
      motorState = stop;
      digitalWrite(enablePin, LOW);
      digitalWrite(backwardsPin, LOW);
      digitalWrite(forwardsPin, LOW);
    }
  }

  void Forwards(){
    if (motorState != forwards){
      motorState = forwards;
      digitalWrite(enablePin, HIGH);
      digitalWrite(backwardsPin, LOW);
      digitalWrite(forwardsPin, HIGH);
    }
  }

  void Backwards(){
    if (motorState != backwards){
      motorState = backwards;
      digitalWrite(enablePin, HIGH);
      digitalWrite(backwardsPin, HIGH);
      digitalWrite(forwardsPin, LOW);
    }
  }
  void Brake(){
    if (motorState != brake){
      motorState = brake;
      digitalWrite(enablePin, HIGH);
      digitalWrite(backwardsPin, HIGH);
      digitalWrite(forwardsPin, HIGH);
    }
  }
};

class MotorPwm : protected Motor{
public:
  MotorPwm(int fwdpin, int bckpin, int enapin): Motor(fwdpin, bckpin, enapin){
    Speed = 255;
  }

  MotorPwm(int fwdpin, int bckpin, int enapin, int speed): Motor(fwdpin, bckpin, enapin){
    Speed = speed;
  }

  void Forwards(){
    if(motorState != forwards){
      motorState = forwards;
      analogWrite(enablePin,Speed);
      digitalWrite(forwardsPin,HIGH);
      digitalWrite(backwardsPin,LOW);
    }
  }

  void Backwards(){
    if (motorState != backwards){
      motorState = backwards;
      analogWrite(enablePin,Speed);
      digitalWrite(forwardsPin,LOW);
      digitalWrite(backwardsPin,HIGH);
    }
  }

  void SetSpeed(int speed){
    if(speed <= 255 && speed >= 0){
      Speed = speed;
    }
    else{
      Speed = 0;
    }
    if ((motorState != brake)||(motorState!=stop)){
      analogWrite(enablePin,Speed);
    }
  }

 protected:
   int Speed;
};

class MotorEncoder : public MotorPwm{
public:
  MotorEncoder(int fwdpin, int bckpin, int enapin, int speed, int intpin) : MotorPwm(fwdpin,bckpin,enapin,speed){
    Count = 0;
    pinMode(intpin, INPUT_PULLUP);
    //attachInterrupt(digitalPinToInterrupt(intpin), increaseCount, CHANGE);
  }

  MotorEncoder(int fwdpin, int bckpin, int enapin, int intpin) : MotorPwm(fwdpin,bckpin,enapin){
    pinMode(intpin, INPUT_PULLUP);
    Count = 0;
    //attachInterrupt(digitalPinToInterrupt(intpin), increaseCount, CHANGE);
  }

  void increaseCount(){
    Count = Count + 1;
  }

  void moveDistance(bool forwards, int distance){ //distance in mm
    if(measuring){
        updateDistance();
    }
    else{
      measuring = true;
      double circumference = PI * Diameter;
      targetCount = (distance / circumference) * steps;
      if (forwards){
        previous = Count;
        MotorPwm::Forwards();
      }
      else{
        previous = Count;
        MotorPwm::Backwards();
      }
    }
  }

  void calculateRPM(){
    Currentmillis = millis();
    rpmCurrent = Count;
    if(Previousmillis == 0){
      Previousmillis = Currentmillis;
    }
    if (Currentmillis-Previousmillis >= 200){
      if (rpmCurrent != 0){
        long elapsed = Currentmillis-Previousmillis;
        float rpmElapsed = (float)(rpmCurrent - rpmPrevious);
        float stepdiv = rpmElapsed/steps;
        rpm = stepdiv*(60000/elapsed);
        Previousmillis = Currentmillis;
        rpmPrevious = rpmCurrent;
      }
    }
  }

  float Getrpm(){
    return rpm;
  }
  void updateDistance(){
    if (measuring){
      distanceAggr += (Count-previous);
      if ((distanceAggr) >= targetCount) {
        Motor::Brake();
        measuring = false;
        distanceAggr = 0;
      }
      else{
        previous = Count;
      }
    }
  }

  long getCount(){
    return Count;
  }

  double getDiameter(){
    return Diameter;
  }

  void setDiameter(double diameter){
    Diameter = diameter;
  }

  void setSteps(int Steps){
    steps = Steps;
  }

  int getSteps(){
    return steps;
  }

  void stopMeasuring(){
    Motor::Stop();
    measuring = false;
  }
protected:
  unsigned long Count = 0L;
  unsigned long previous = 0;
  unsigned long rpmPrevious = 1;
  unsigned long rpmCurrent = 0;
  float rpm = 0.0;
  unsigned long Currentmillis;
  unsigned long Previousmillis = millis();
  double Diameter = 65.0; //mm
  int steps = 20; // number of pules on encoder per revolution
  bool measuring = false;
  int targetCount = 0;
  int distanceAggr = 0;
};
