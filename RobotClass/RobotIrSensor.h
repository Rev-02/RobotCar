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

public IrSensorAnalogue : public IrSensor{
public:
  IrSensorAnalogue(int pin, int thresh){
    Pin = pin;
    Thresh = thresh;
  }
  bool getStatus() override{
    if (analogRead(pin) < Thresh){
      return true;
    }
    else{
      return false;
    }
  }
}
