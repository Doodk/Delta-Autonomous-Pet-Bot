/*
ver 1.0.0.61115
  - [MOD] Motor controls(left and right)
  - [MOD] Button controls
  - [ADD] Play sound feature

ver 1.0.0.61104
  - [ADD] UltraSonic and Motor controls
*/

#define trigPin 7
#define echoPin 6

#define btnStart 3

#include "MotorDriver.h"
MotorDriver motor;
bool btnStartOn;
bool btnStartHeld;
void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(btnStart, INPUT_PULLUP);  

  //pinMode(led, OUTPUT);
  //pinMode(led2, OUTPUT);
  
  btnStartOn = false;
  btnStartHeld = false;
  motor.begin();
}

//long inputArr[];
//long outputArr[];
void loop() {
  if (digitalRead(btnStart)==LOW){
    if (!btnStartHeld){
      btnStartOn = !btnStartOn;
      btnStartHeld = true;
    }
  } else {
    btnStartHeld = false;
  }
  
  if (btnStartOn){
    if (GetDistance()<50){
      Move(-200,-200);
      Sound();
    }else {
      Move(100,100);
    }
  }else {
    Stop();
  }
}

long GetDistance() {
  long duration, Distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  Distance = (duration / 2) / 29.1;
  if (Distance >= 200 || Distance <= 0)
    return 9999;
  return Distance; 
}

void MoveLeft(long speedX) {
  const int leftMotor = 1;
  if (speedX==0)
    motor.brake(leftMotor);
  else
    motor.speed(leftMotor, -speedX);
}

void MoveLeft(long speedX, unsigned long runTime) {
  const int leftMotor = 1;
  if (speedX==0)
    motor.brake(leftMotor);
  else
    motor.speed(leftMotor, -speedX);
}

void MoveRight(long speedX) {
  const int rightMotor = 0;
  if (speedX==0)
    motor.brake(rightMotor);
  else
    motor.speed(rightMotor, -speedX);
}

void Move(long leftSpeed, long rightSpeed) {
  MoveLeft(leftSpeed);
  MoveRight(rightSpeed);
}

void Move(long singleSpeed) {
  Move(singleSpeed, singleSpeed);
}

void Stop(){
  Move(0);
}

void Sound() {
  //31  65535
  tone(2, 1760, 1000) ; 
}


/*
long mvRnd_startTime = 0; 
//long mvRnd_interval = 1000;
void MoveRandom(long totalTime) {
  unsigned long curTime = millis();
  if (mvRnd_startTime==0){
    mvRnd_startTime = curTime;
    //Move(random,random);
  } else if (curTime - mvRnd_startTime < totalTime){
    myRnd_startTime = 0;
    Move(0);
  }
}
*/
