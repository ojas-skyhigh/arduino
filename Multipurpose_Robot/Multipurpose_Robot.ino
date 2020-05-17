
/*****************************************************************************************************************************************
  Made by and owned by DMNR pvt.ltd
  # Confidential document.
  Do not open without permission from either member's permission.
  Program by Ojas.
  App by Mrigaank.
******************************************************************************************************************************************/
#include <LedControl.h>
                           
int DIN = 10;
int CS =  9;
int CLK = 8;

int right_sensor = A2; //Right Infra-red sensor
int left_sensor = A3; //Left Infra-red sensor
int trig_pin = 7;     //Trig pin for the Ultra-sonic sensor
int echo_pin = A0;    //Echo pin for the Ultra-sonic sensor
int motor_right_f = 3; //Forward direction right motor
int motor_right_b = 5; // Backward direction right motor
int motor_left_f = 6; //Forward direction left motor
int motor_left_b = 9; //Backward direction left motor

int follow_button = 8; //Button to follow
int retreat_button = 10; //Button to retreat

char data = 0;

byte smile[8] = { 0x3C, 0x42, 0xA5, 0x81, 0xA5, 0x99, 0x42, 0x3C };
byte sad[8] = { 0x3C , 0x42, 0xA5, 0x81, 0x99, 0xA5, 0x42, 0x3C };

LedControl lc = LedControl(DIN, CLK, CS, 0);

void setup() {

  Serial.begin(9600);

  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  pinMode(motor_right_f, OUTPUT);
  pinMode(motor_right_b, OUTPUT);
  pinMode(motor_left_f, OUTPUT);
  pinMode(motor_left_b, OUTPUT);

  pinMode(left_sensor, INPUT);
  pinMode(right_sensor, INPUT);
  pinMode(follow_button, INPUT);
  pinMode(retreat_button, INPUT);

  lc.shutdown(0, false);
  lc.setIntensity(0, 15);
  lc.clearDisplay(0);

}


void loop() {

  int distance = CheckObstacle(echo_pin, trig_pin);
  ButtonInput(follow_button, retreat_button);

}

/******************************************************************************************************************************************
 * Fuctions (Not part of the Loop).
 *****************************************************************************************************************************************/

int CheckObstacle(int My_trig_pin, int My_echo_pin) {

  int duration = pulseIn(My_echo_pin, HIGH);
  int distance = duration * 0.034 / 2;

  digitalWrite(My_trig_pin, LOW);
  delayMicroseconds(2);

  digitalWrite(My_trig_pin, HIGH);
  delayMicroseconds(2);
  digitalWrite(My_trig_pin, LOW);


  return distance;
}

void followProcedure(int My_motor_right_f, int My_motor_left_f, int My_motor_left_b, int My_motor_right_b, int My_Right_sensor, int My_Left_sensor ) {

  lc.clearDisplay(0);

  //printByte(smile);
  delay(1000);

  int Right_Value = analogRead(My_Right_sensor);
  int Left_Value = analogRead(My_Left_sensor);

  if ((Right_Value == 1) && (CheckObstacle(echo_pin, trig_pin) >= 10 && CheckObstacle(echo_pin, trig_pin) <= 30) && (Left_Value == 1)) {
    analogWrite(My_motor_right_f, 120);
    analogWrite(My_motor_left_f, 120);
  }
  else if ((Right_Value == 0) && (Left_Value == 1)) {
    analogWrite(My_motor_right_f, 200);
    analogWrite(My_motor_left_b, 100); //Going to left(f)
  }
  else if ((Right_Value == 1) && (Left_Value == 0)) {
    analogWrite(My_motor_right_b, 100);
    analogWrite(My_motor_left_f, 200); // Going to right(f)
  }
  else if ((Right_Value == 1) && (Left_Value == 1)) {
    analogWrite(My_motor_right_b, 120);
    analogWrite(My_motor_left_b, 120);
  }

}

void retreatProcedure(int My_motor_right_f, int My_motor_left_f, int My_motor_left_b, int My_motor_right_b, int My_Right_sensor, int My_Left_sensor ) {

  lc.clearDisplay(0);
  printByte(sad);
  delay(1000);

  int Right_Value = analogRead(My_Right_sensor);
  int Left_Value = analogRead(My_Left_sensor);

  if ((Right_Value == 1) && (CheckObstacle(echo_pin, trig_pin) >= 10 && CheckObstacle(echo_pin, trig_pin) <= 30) && (Left_Value == 1)) {
    analogWrite(My_motor_right_b, 120);
    analogWrite(My_motor_left_b, 120);
  }
  else if ((Right_Value == 0) && (Left_Value == 1)) {
    analogWrite(My_motor_right_b, 100);
    analogWrite(My_motor_left_f, 200); //Going to right
  }
  else if ((Right_Value == 1) && (Left_Value == 0)) {
    analogWrite(My_motor_right_f, 200);
    analogWrite(My_motor_left_b, 100); //Going to left
  }
  else if ((Right_Value == 1) && (Left_Value == 1)) {
    analogWrite(My_motor_right_f, 100);
    analogWrite(My_motor_left_f, 100);
  }

}

void ButtonInput(int My_follow_button, int My_retreat_button) {

  int follow_state = digitalRead(My_follow_button);
  int retreat_state = digitalRead(My_retreat_button);

  if (follow_state == HIGH) {
    delay(10);
    if (follow_state == HIGH)
    {
      while (follow_state == HIGH);
      delay(10);
      while (follow_state == HIGH);
      follow_state = !follow_state;
      followProcedure(motor_right_f, motor_right_b, motor_left_f, motor_left_b, right_sensor, left_sensor);
    }
  }

  else if (retreat_state == HIGH) {
    delay(10);
    if (retreat_state == HIGH)
    {
      while (retreat_state == HIGH);
      delay(10);
      while (retreat_state == HIGH);
      retreat_state = !retreat_state;
      retreatProcedure(motor_right_f, motor_right_b, motor_left_f, motor_left_b, right_sensor, left_sensor);

    }
  }

}
