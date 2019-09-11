
#include <Servo.h>

int pot_pin_claw = A0;
int pot_pin_bottom = A1;
int pot_pin_joint1 = A2;
int pot_pin_joint2 = A3;

int prev_value[3];

int value_claw;
int value_bottom;
int value_joint1;
int value_joint2;

Servo servo_claw;
Servo servo_bottom;
Servo servo_joint1;
Servo servo_joint2;

void setup() {
  servo_claw.attach(2);
  servo_bottom.attach(3);
  servo_joint1.attach(4);
  servo_joint2.attach(5);

  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  Serial.begin(9600);
}

void loop() {
  int pot_inputs[3];
  
  pot_inputs[0] = analogRead(pot_pin_claw);
  pot_inputs[1] = analogRead(pot_pin_bottom);
  pot_inputs[2] = analogRead(pot_pin_joint1);
  pot_inputs[3] = analogRead(pot_pin_joint2);

  if(pot_inputs[0] > 511) {
    value_claw = 1;
  } else {
    value_claw = 0;
  }
  
  value_bottom = map(pot_inputs[1],110,800,180,0);
  value_joint1 = map(pot_inputs[2],1023,600,30,160);
  value_joint2 = map(pot_inputs[3],170,880,180,0);

  if(value_claw) {
    servo_claw.write(80);
  } else {
    servo_claw.write(50);
  }
  
  //servo movements for bottom 
  if(prev_value[1] < value_bottom)
  {
    for(int i = prev_value[1] ; i < value_bottom ; i+=2)
    servo_bottom.write(i);
    delay(5);
  } else 
  {
    for(int i = value_bottom ; i > prev_value[1] ; i-=2)
    servo_bottom.write(i);
    delay(5);
  }
  
  //servo movements for joint1 
  if(prev_value[2] < value_bottom)
  {
    for(int i = prev_value[2] ; i < value_joint1 ; i+=2)
    servo_joint1.write(i);
    delay(5);
  } else 
  {
    for(int i = value_joint1 ; i > prev_value[2] ; i-=2)
    servo_joint1.write(i);
    delay(5);
  }
  
  //servo movements for joint2 
  if(prev_value[3] < value_bottom)
  {
    for(int i = prev_value[3] ; i < value_joint2 ; i+=2)
    servo_joint2.write(i);
    delay(5);
  } else 
  {
    for(int i = value_joint2 ; i > prev_value[3] ; i-=2)
    servo_joint2.write(i);
    delay(5);
  }

  

  delay(5);
  // prev_value[0] = value_claw;
  prev_value[1] = value_bottom;
  prev_value[2] = value_joint1;
  prev_value[3] = value_joint2;
}
