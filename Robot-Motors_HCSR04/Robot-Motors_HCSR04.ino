#define enable_pin_r 5
#define enable_pin_l 3
#define lm_fwd 11
#define lm_bwd 12
#define rm_fwd 9
#define rm_bwd 10
#define trig A4
#define echo A5
#define motor_speed 200 //max 255
#define dist_threshold 10 //20 is safe
bool trig1 = false;
void setup() {
  // put your setup code here, to run once:
pinMode(enable_pin_r, OUTPUT);
pinMode(enable_pin_l, OUTPUT);
pinMode(lm_fwd, OUTPUT);
pinMode(lm_bwd, OUTPUT);
pinMode(rm_fwd, OUTPUT);
pinMode(rm_bwd, OUTPUT);
pinMode(trig,OUTPUT);
pinMode(echo,INPUT);
Serial.begin(9600);
}

void move_motor(int motor_state,int fwd_pin,int bwd_pin, int en, int m_speed) {
  // put your main code here, to run repeatedly:
  if (motor_state == 1){ //forwards
    digitalWrite(fwd_pin, HIGH);
    digitalWrite(bwd_pin, LOW);
    analogWrite(en, m_speed);
    //Serial.println("forwards");
  } else if(motor_state == 2){ //backwards
    //Serial.println("backwards");
    digitalWrite(fwd_pin, LOW);
    digitalWrite(bwd_pin, HIGH);
    analogWrite(en, m_speed);
  }
  else{
     digitalWrite(fwd_pin, LOW);
    digitalWrite(bwd_pin, LOW);
    analogWrite(en, 0);
    //Serial.println("STOP");
  }
}

void forwards(){
  move_motor(1,lm_fwd,lm_bwd,enable_pin_l,motor_speed);
  move_motor(1,rm_fwd,rm_bwd,enable_pin_r,motor_speed);
}

void stopMoving(){
  move_motor(0,lm_fwd,lm_bwd,enable_pin_l,motor_speed);
  move_motor(0,rm_fwd,rm_bwd,enable_pin_r,motor_speed);
}

void turn(bool clockwise, int mil){
  if(clockwise){
    move_motor(1,lm_fwd,lm_bwd,enable_pin_l,motor_speed);
    move_motor(2,rm_fwd,rm_bwd,enable_pin_r,motor_speed);
    delay(mil);
    stopMoving();
  }
  else{
    move_motor(2,lm_fwd,lm_bwd,enable_pin_l,motor_speed);
    move_motor(1,rm_fwd,rm_bwd,enable_pin_r,motor_speed);
    delay(mil);
    stopMoving();
  }
}

void backwards(){
  move_motor(2,lm_fwd,lm_bwd,enable_pin_l,motor_speed);
  move_motor(2,rm_fwd,rm_bwd,enable_pin_r,motor_speed);
}

int checkDistance(){
 digitalWrite(trig, LOW);
 delayMicroseconds(2);

 digitalWrite(trig, HIGH);
 delayMicroseconds(10);

 digitalWrite(trig, LOW);
 int dur = pulseIn(echo, HIGH);

 //Calculate the distance (in cm) based on the speed of sound.
 int distance = dur/58.2;
 return distance;

}

void loop(){
  if (checkDistance() > dist_threshold){
    forwards();
  }
  else{
    if(trig1){
      backwards();
      delay(300);
      stopMoving();
      //delay(500);
      turn(random(2),300);
      trig1 = false;
  }
  else{
    trig1 = true;
  }
  }
}
