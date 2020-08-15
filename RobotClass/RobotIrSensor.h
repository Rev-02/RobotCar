class IrSensor{
public:
  IrSensor(int pin){
  pinMode(pin, INPUT_PULLUP);
  Pin = pin;
  }
  bool getStatus(){
    return digitalRead(Pin);
  }
protected:
  int Pin;
};
