#define enable_pin 5
#define enable_pin2 3
#define m1_fwd 9
#define m1_bwd 10
#define m2_fwd 11
#define m2_bwd 12
#define motor_speed 150 //max 255

void setup() {
  // put your setup code here, to run once:
pinMode(enable_pin, OUTPUT);
pinMode(enable_pin2, OUTPUT);
pinMode(m1_fwd, OUTPUT);
pinMode(m1_bwd, OUTPUT);
pinMode(m2_fwd, OUTPUT);
pinMode(m2_bwd, OUTPUT);
Serial.begin(9600);
move_motor(1,m1_fwd,m1_bwd,enable_pin);
move_motor(2,m2_fwd,m2_bwd,enable_pin2);
}

void move_motor(int motor_state,int fwd_pin,int bwd_pin, int en) {
  // put your main code here, to run repeatedly:
  if (motor_state == 1){ //forwards
    digitalWrite(fwd_pin, HIGH);
    digitalWrite(bwd_pin, LOW);
    analogWrite(en, motor_speed);
    //Serial.println("forwards");
  } else if(motor_state == 2){ //backwards
    //Serial.println("backwards");
    digitalWrite(fwd_pin, LOW);
    digitalWrite(bwd_pin, HIGH);
    analogWrite(en, motor_speed);
  }
  else{
     digitalWrite(fwd_pin, LOW);
    digitalWrite(bwd_pin, LOW);
    analogWrite(en, 0);
    //Serial.println("STOP");
  }
}

void loop(){
  delay(100);
}
