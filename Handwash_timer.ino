
int trig_pin = 8;
int echo_pin = A0;
int red_led = 13;
int green_led = 4;
int blue_led = 5;
int tap_led = 2;
int buzzer_pin = 7;
int button_pin = 6;
int message_led = 3;

int Pin0 = 9;
int Pin1 = 10;
int Pin2 = 11;
int Pin3 = 12;

int _step = 512; // Each step = 0.7 degree
int _speed = 1;

int counter = 0;

volatile int buttonState = LOW;

void setup() {

  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  pinMode(red_led, OUTPUT);
  pinMode(green_led, OUTPUT);
  pinMode(buzzer_pin, OUTPUT);
  pinMode(blue_led, OUTPUT);
  pinMode(tap_led, OUTPUT);
  pinMode(message_led, OUTPUT);
  pinMode(button_pin, INPUT);
  pinMode(Pin0, OUTPUT);
  pinMode(Pin1, OUTPUT);
  pinMode(Pin2, OUTPUT);
  pinMode(Pin3, OUTPUT);

  Serial.begin(9600);
  counter = 0;
}

void loop() {

beginning:
  delay(3000);
  buttonState = digitalRead(button_pin);

  if (checkHands(trig_pin, echo_pin) <= 25) {

    Serial.println(" ");
    Serial.println("Hand detected");
    startProcedure(blue_led, tap_led);
    checkHands(trig_pin, echo_pin);
    checkHands(trig_pin, echo_pin);
    //Serial.println(counter);
waiting:
    Serial.println("Waiting for button press");
    analogWrite(message_led, 255); // Enter appropiate brightness for LED (from 0-255).(Tip-try "100")

    if (digitalRead(button_pin) == HIGH) {
      delay(10);
      if (digitalRead(button_pin) == HIGH)
      {
        while (digitalRead(button_pin) == HIGH);
        delay(10);
        while (digitalRead(button_pin) == HIGH);
        buttonState = !buttonState;
        analogWrite(message_led, 0);
        Speed(15);
        Step(64);
        Serial.println(" ");
        Serial.println("20 seconds left");
        Serial.println(counter);
        counter++;
        delay(3000);

        while (checkHands(trig_pin, echo_pin) <= 25) {

          checkHands(trig_pin, echo_pin);
          delay(2000);
          Speed(15);
          Step(64);
          Serial.println("15 seconds left");
          checkHands(trig_pin, echo_pin);
          counter ++;
          Serial.println(counter);

          while (checkHands(trig_pin, echo_pin) <= 25) {

            checkHands(trig_pin, echo_pin);
            fiveSecondProcedure();
            Serial.println("10 seconds left");
            checkHands(trig_pin, echo_pin);
            counter ++;
            Serial.println(counter);

            while (checkHands(trig_pin, echo_pin) <= 25) {

              checkHands(trig_pin, echo_pin);
              fiveSecondProcedure();
              Serial.println("5 seconds left");
              checkHands(trig_pin, echo_pin);
              counter ++;
              Serial.println(counter);

              while (checkHands(trig_pin, echo_pin) <= 25) {

                checkHands(trig_pin, echo_pin);
                fiveSecondProcedure();
                Serial.println("No seconds left");
                //Serial.println(checkHands(trig_pin, echo_pin));
                checkHands(trig_pin, echo_pin);
                counter ++;
                Serial.println(counter);

                while (checkHands(trig_pin, echo_pin) <= 25 && counter == 5) {

                  timeUp(green_led, buzzer_pin, tap_led);
                  Serial.println(" ");
                  Serial.println("You have washed your hands properly");
                  counter = 0;
                  checkHands(trig_pin, echo_pin);

                  while (checkHands(trig_pin, echo_pin) <= 25 && counter == 0) {
                    //Serial.println("I am here-while beginning loop");
                    goto beginning;
                  }

                  while (checkHands(trig_pin, echo_pin) > 25 && counter != 0) {
                    continue;
                  }
                  //Serial.println("I am here-while loop");
                  timeNotUp(red_led, buzzer_pin);
                  delay(2000);
                }
              }
            }// Normal brackets
          }
        }
        if (checkHands(trig_pin, echo_pin) > 25 && counter != 0) {
          //Serial.println("I am here-if loop");
          timeNotUp(red_led, buzzer_pin);
          delay(2000);
        }
        else if (checkHands(trig_pin, echo_pin) <= 25 && counter == 0) {
          //Serial.println("I am here-if beginning loop");
          goto beginning;
        }
      }
    }
    else if (buttonState == LOW) {
      //Serial.println("I am here - waiting");
      analogWrite(message_led, 255);
      goto waiting;
    }
  }
}
/***************************************************************************************************************************************
   Fuctions (Not part of the Loop).
****************************************************************************************************************************************/

int checkHands(int My_trig_pin, int My_echo_pin) {

  digitalWrite(My_trig_pin, LOW);
  delayMicroseconds(2);

  digitalWrite(My_trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(My_trig_pin, LOW);

  int duration = pulseIn(My_echo_pin, HIGH);
  int distance = duration * 0.034 / 2;

  return distance;
}

void startProcedure(int My_blue_led, int My_tap_led) {

  digitalWrite(My_blue_led, HIGH);
  delay(100);
  digitalWrite(My_blue_led, LOW);
  Speed(15);
  Step(64);
  digitalWrite(My_tap_led, HIGH);
  delay(3000);
  digitalWrite(My_tap_led, LOW);
}

void timeUp(int My_green_led, int My_buzzer_pin, int My_tap_led) {

  digitalWrite(My_green_led, HIGH);
  digitalWrite(My_buzzer_pin, HIGH);
  delay(1000);
  digitalWrite(My_green_led, LOW);
  digitalWrite(My_buzzer_pin, LOW);
  counter = 0;
  digitalWrite(My_tap_led, HIGH);
  delay(8000);
  digitalWrite(My_tap_led, LOW);
  Speed(15);
  Step(128);
}

void displayMessage_5() {
  Speed(15);
  Step(64);
}
void displayMessage_4() {
  Speed(15);
  Step(128);
}
void displayMessage_3() {
  Speed(15);
  Step(192);
}
void displayMessage_2() {
  Speed(15);
  Step(256);
}
void displayMessage_1() {
  Speed(15);
  Step(320);
}

void timeNotUp(int My_red_led, int My_buzzer_pin) {

  digitalWrite(My_red_led, HIGH);
  digitalWrite(My_buzzer_pin, HIGH);
  delay(500);
  digitalWrite(My_buzzer_pin, LOW);
  delay(500);
  digitalWrite(My_buzzer_pin, HIGH);
  delay(500);
  digitalWrite(My_buzzer_pin, LOW);
  delay(500);
  digitalWrite(My_buzzer_pin, HIGH);
  delay(500);
  digitalWrite(My_buzzer_pin, LOW);
  digitalWrite(My_red_led, LOW);
  Serial.println(checkHands(trig_pin, echo_pin));

  if (counter == 1) {
    displayMessage_1();
    delay(2000);
    Speed(15);
    Step(64);
  }
  else if (counter == 2) {
    displayMessage_2();
    delay(2000);
    Speed(15);
    Step(64);
  }
  else if (counter == 3) {
    displayMessage_3();
    delay(2000);
    Speed(15);
    Step(64);
  }
  else if (counter == 4) {
    displayMessage_4();
    delay(2000);
    Speed(15);
    Step(64);
  }
  else if (counter == 5) {
    displayMessage_5();
    delay(2000);
    Speed(15);
    Step(64);
  }
  
  Serial.println(counter);
  counter = 0;

  Serial.println(" ");
  Serial.println("You did not wash your hands properly , wash again !");
  Serial.println(checkHands(trig_pin, echo_pin));
}

void Speed(int stepperspeed) { // Set speed
  _speed = 15 - stepperspeed;
  if ( _speed < 1) {
    _speed = 1;
  }
  if ( _speed > 15) {
    _speed = 15;
  }
}

void Step(int _step) {

  if (_step >= 0) { // Forward rotation
    for (int i = 0; i < _step; i++) {
      setStep(1, 0, 0, 1);
      delay(_speed);
      setStep(1, 0, 0, 0);
      delay(_speed);
      setStep(1, 1, 0, 0);
      delay(_speed);
      setStep(0, 1, 0, 0);
      delay(_speed);
      setStep(0, 1, 1, 0);
      delay(_speed);
      setStep(0, 0, 1, 0);
      delay(_speed);
      setStep(0, 0, 1, 1);
      delay(_speed);
      setStep(0, 0, 0, 1);
      delay(_speed);
    }
  }

  else { // Backward rotation
    for (int i = _step; i < 0; i++) {
      setStep(0, 0, 0, 1);
      delay(_speed);
      setStep(0, 0, 1, 1);
      delay(_speed);
      setStep(0, 0, 1, 0);
      delay(_speed);
      setStep(0, 1, 1, 0);
      delay(_speed);
      setStep(0, 1, 0, 0);
      delay(_speed);
      setStep(1, 1, 0, 0);
      delay(_speed);
      setStep(1, 0, 0, 0);
      delay(_speed);
      setStep(1, 0, 0, 1);
      delay(_speed);
    }
  }
}

void setStep(int a, int b, int c, int d) {
  digitalWrite(Pin0, a);
  digitalWrite(Pin1, b);
  digitalWrite(Pin2, c);
  digitalWrite(Pin3, d);
}

void fiveSecondProcedure() {

  checkHands(trig_pin, echo_pin);
  delay(5000);
  Speed(15);
  Step(64); // 64
}
