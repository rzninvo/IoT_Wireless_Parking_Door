#include <Servo.h>

Servo parking_motor;
int yellow_light = 33;
int trigPin = 45;
int echoPin = 46;
char input;

bool check_obstacle(){
  long dur;
  int distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  dur = pulseIn(echoPin, HIGH);
  distance = dur * 0.034 / 2;
  if (distance < 60)
    return true;
  else 
    return false;
  return false;
}

void rotate_parking_door(int sign = 1)
{
  int cur_degree = parking_motor.read();
  if (sign == 1){
    for (int i = cur_degree; i < 90; i++){
          parking_motor.write(i);
          if ((i % 10) < 5)
            digitalWrite(yellow_light, LOW);
          else 
            digitalWrite(yellow_light, HIGH);
          delay(110);
          input = Serial.read();
          if (input == '3'){
            delay(1000);
            rotate_parking_door(-1);
            return;
          }
        }
    }
  if (sign == -1){
    for (int i = cur_degree; i > 0; i--){
      parking_motor.write(i);
        if ((i % 10) < 5)
          digitalWrite(yellow_light, LOW);
        else 
          digitalWrite(yellow_light, HIGH);
        delay(110);
        input = Serial.read();
        if (input == '1'){
          delay(1000);
          rotate_parking_door();
          return;
        }
        else if (check_obstacle()){
          delay(1000);
          rotate_parking_door(1);
          return;
        }
    }
  }
}

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);
  parking_motor.attach(40,1000,2000);
  parking_motor.write(0);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(yellow_light, OUTPUT);
}

void loop() {
  if (Serial.available() > 0){
    input = Serial.read();
    if (input == '1'){
      rotate_parking_door();
    }
    else if (input == '3'){
      rotate_parking_door(-1);
    }
  }
}
