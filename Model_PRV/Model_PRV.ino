/*
   If 2 motors don't provide enough power connect 4 motors.
*/
#include <AFMotor.h>
#include <Servo.h>

AF_DCMotor motor_right(2);
AF_DCMotor motor_left(1);
AF_DCMotor soil_driller(3);

Servo neck_motor;

int trig_pin_l = A1; // 7
int echo_pin_l = A0;
int trig_pin_r = A2; //8
int echo_pin_r = A3;
int soil_driller = A4; // 2


void setup() {

  neck_motor.attach(9);

  pinMode(trig_pin_l, OUTPUT);
  pinMode(echo_pin_l, INPUT);
  pinMode(trig_pin_r, OUTPUT);
  pinMode(echo_pin_r, INPUT);
  pinMode(soil_driller, OUTPUT);

}

void loop() {

  /*  if (wifi module gives automatic mode signal) {
      AutomaticMode();
    }

    if (wifi module gives Manual Mode signal) {
      ManualMode();
    }*/
}

void AutomaticMode() {

  neck_motor.write(-90);

  digitalWrite(trig_pin_l, LOW);
  delayMicroseconds(2);

  digitalWrite(trig_pin_l, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin_l, LOW);

  int duration_left = pulseIn(echo_pin_l, HIGH);
  int distance_left = duration_left * 0.034 / 2;

  digitalWrite(trig_pin_r, LOW);
  delayMicroseconds(2);

  digitalWrite(trig_pin_r, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin_r, LOW);

  int duration_right = pulseIn(echo_pin_r, HIGH);
  int distance_right = duration_right * 0.034 / 2;

  if (distance_right <= 10 && distance_left <= 10) {
    Stop();
    Back();
    Right();
  }

  else if (distance_right > 10 && distance_left > 10) {
    Front();
  }

  else if (distance_left <= 10) {
    Right();
  }

  else if (distance_right <= 10) {
    Left();
  }
}

void ManualMode() {

  if ( front signal is given) {
    Front();
  }
  else if ( back signal is given) {
    Back();
  }
  else if ( right signal is given) {
    Right();
  }
  else if ( left signal is given) {
    Left();
  }
  else if ( stop signal is given) {
    Stop();
  }
  if ( neck turn signal is given) {
    neck_motor.write(turn signal);
  }
  if ( drill signal is given) {
    drill();
  }
}
void Left() {

  motor_right.setSpeed(150);
  motor_right.run(FORWARD);
  motor_left.run(RELEASE);
}

void Back() {

  motor_left.setSpeed(150);
  motor_right.setSpeed(150);

  motor_left.run(BACKWARD);
  motor_right.run(BACKWARD);
}

void Right() {

  motor_left.setSpeed(150);
  motor_left.run(FORWARD);
  motor_right.run(RELEASE);
}

void Front() {

  motor_left.setSpeed(250);
  motor_right.setSpeed(250);

  motor_left.run(FORWARD);
  motor_right.run(FORWARD);
}

void Stop() {

  motor_left.run(RELEASE);
  motor_right.run(RELEASE);
}

void drill() {

  soil_driller.setSpeed(250);
  soil_driller.run(FORWARD);
}
