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
 protected:
   int Speed;
};
