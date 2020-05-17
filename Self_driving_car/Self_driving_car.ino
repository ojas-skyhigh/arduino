/*****************************************************************************************************************************************
   Created and owned by #DMNR.
   #Confidential.Do not open without permission of either of the members.
   Program made by Ojas.
   Circuitry by Ojas and Mrigaank.
   Structure by Ojas,Mrigaank and Sourish.
*/

#define S0  9
#define S1   10
#define S2   11
#define S3   12
#define sensorOut  13

int trig_pin_left = 6;
int echo_pin_left = A4;
int trig_pin_right = 5;
int echo_pin_right = A0;
int motor_right = 3;
int motor_left = 4;
int photoresistor = A2;
int redfrequency;
int bluefrequency;
int greenfrequency;
int day_state;//
int night_state;// -450

long duration_right;
long distance_right;
long duration_left;
long distance_left;

void setup() {

  pinMode(trig_pin_left, OUTPUT);
  pinMode(echo_pin_right, INPUT);
  pinMode(trig_pin_right, OUTPUT);
  pinMode(echo_pin_left, INPUT);
  pinMode(motor_right, OUTPUT);
  pinMode(motor_left, OUTPUT);
  pinMode(photoresistor, INPUT);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  Serial.begin(9600);
}

void loop() {

  CheckObstacles(trig_pin_left, echo_pin_right, trig_pin_right, echo_pin_left, motor_right, motor_left, photoresistor);
  Colour_detection(S2, S3, photoresistor, motor_right, motor_left);
}

/****************************************************************************************************************************************
   Functions(Not part of the Loop).
 ****************************************************************************************************************************************/

void Colour_detection(int My_S2, int My_S3, int My_photoresistor, int My_motor_left, int My_motor_right) {

  int value = analogRead(My_photoresistor);

  digitalWrite(My_S2, LOW);
  digitalWrite(My_S3, LOW);

  redfrequency = pulseIn(sensorOut, LOW);
  redfrequency = map(redfrequency, 25, 72, 255, 0);

  if (value == day_state) {

    value == day_state;

    if (redfrequency > value) {

    }

    Serial.print("R= ");
    Serial.print(redfrequency);
    delay(100);

    digitalWrite(My_S2, HIGH);
    digitalWrite(My_S3, HIGH);

    greenfrequency = pulseIn(sensorOut, LOW);
    greenfrequency = map(greenfrequency, 30, 90, 255, 0);

    if (greenfrequency > value) {

    }

    Serial.print(" G= ");
    Serial.print(greenfrequency);
    delay(100);

    digitalWrite(My_S2, LOW);
    digitalWrite(My_S3, HIGH);
    /*
        bluefrequency = pulseIn(sensorOut, LOW);
        bluefrequency = map(bluefrequency, 25, 70, 255, 0);

        if (bluefrequency > value) {

        }
        delay(100);
    */
  }

  else if (value == night_state) {

    value == -450;

    if (redfrequency > value) {

      digitalWrite(My_motor_right, LOW);
      digitalWrite(My_motor_left, LOW);

    }

    Serial.print("R= ");
    Serial.print(redfrequency);
    delay(100);

    digitalWrite(My_S2, HIGH);
    digitalWrite(My_S3, HIGH);

    greenfrequency = pulseIn(sensorOut, LOW);
    greenfrequency = map(greenfrequency, 30, 90, 255, 0);

    if (greenfrequency > value) {

      digitalWrite(My_motor_right, HIGH);
      digitalWrite(My_motor_left, HIGH);
    }

    Serial.print(" G= ");
    Serial.print(greenfrequency);
    delay(100);
    /*
        digitalWrite(My_S2, LOW);
        digitalWrite(My_S3, HIGH);

        bluefrequency = pulseIn(sensorOut, LOW);
        bluefrequency = map(bluefrequency, 25, 70, 255, 0);

        if (bluefrequency > value) {

        }
        delay(100);
    */

    return redfrequency;
  }

}

void CheckObstacles(int My_trig_pin_left, int My_trig_pin_right, int My_echo_pin_right, int My_echo_pin_left, int My_motor_left, int My_motor_right, int My_photoresistor) {

  digitalWrite(My_trig_pin_left, LOW);
  delayMicroseconds(2);

  digitalWrite(My_trig_pin_left, HIGH);
  delayMicroseconds(10);
  digitalWrite(My_trig_pin_left, LOW);

  int duration_left = pulseIn(My_echo_pin_left, HIGH);
  int distance_left = duration_left * 0.034 / 2;

  digitalWrite(My_trig_pin_right, LOW);
  delayMicroseconds(2);

  digitalWrite(My_trig_pin_right, HIGH);
  delayMicroseconds(10);
  digitalWrite(My_trig_pin_right, LOW);

  int duration_right = pulseIn(My_echo_pin_right, HIGH);
  int distance_right = duration_right * 0.034 / 2;

  int value = analogRead(My_photoresistor);

  if (value == day_state) {

    value == day_state;

    if (distance_right <= 10 && distance_left <= 10 && redfrequency < value) {
      digitalWrite(My_motor_right, LOW);
      digitalWrite(My_motor_left, LOW);
    }

    else if (distance_right > 10 && distance_left > 10 && redfrequency < value) {
      digitalWrite(My_motor_right, HIGH);
      digitalWrite(My_motor_left, HIGH);
    }

    else if (distance_left <= 10 && redfrequency < value) {
      digitalWrite(My_motor_right, HIGH);
      digitalWrite(My_motor_left, LOW);
    }

    else if (distance_right <= 10 && redfrequency < value) {

      digitalWrite(My_motor_right, LOW);
      digitalWrite(My_motor_left, HIGH);
    }
  }

  else if (value == night_state) {

    value == -450;

    if (distance_right <= 10 && distance_left <= 10 && redfrequency < value) {
      digitalWrite(My_motor_right, LOW);
      digitalWrite(My_motor_left, LOW);
    }

    else if (distance_right > 10 && distance_left > 10 && redfrequency < value) {
      digitalWrite(My_motor_right, HIGH);
      digitalWrite(My_motor_left, HIGH);
    }

    else if (distance_left <= 10 && redfrequency < value) {
      digitalWrite(My_motor_right, HIGH);
      digitalWrite(My_motor_left, LOW);
    }

    else if (distance_right <= 10 && redfrequency < value) {

      digitalWrite(My_motor_right, LOW);
      digitalWrite(My_motor_left, HIGH);
    }
  }
}
