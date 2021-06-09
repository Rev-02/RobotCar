class IrSensor{
public:
  IrSensor(int pin){
  pinMode(pin, INPUT_PULLUP);
  Pin = pin;
  }
  virtual bool getStatus(){
    return digitalRead(Pin);
  }
protected:
  int Pin;
};

class IrSensorAnalogue : public IrSensor{
public:
  IrSensorAnalogue(int pin, int thresh) : IrSensor(pin){
    Pin = pin;
    Thresh = thresh;
  }
  bool getStatus() override{
    if (analogRead(Pin) < Thresh){
      return true;
    }
    else{
      return false;
    }
  }
protected:
  int Thresh;
};
