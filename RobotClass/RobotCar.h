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

class MotorPwm : Motor{
  MotorPwm(int fwdpin, int bckpin, int enapin): Motor(fwdpin, bckpin, enapin){
    Speed = 255;
  }

  MotorPwm(int fwdpin, int bckpin, int enapin, int speed): Motor(fwdpin, bckpin, enapin){
    Speed = speed;
  }

  void Forwards(){
    if(motorState != forwards){
      analogWrite(enapin,Speed);
      digitalWrite(forwardsPin,HIGH);
      digitalWrite(backwardsPin,LOW);
    }
  }

  void Backwards(){
    if (motorState != backwards){
      analogWrite(enapin,speed);
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
