/*
   Created by Ojas Patil
   VII A / G.N.S
   For Science Day
   Date - 28/2/2020
*/

int x;

int door_magnet = 9;
int safe_magnet = 10;
int led_red = 12;
int led_green = 11;
int buzzer_pin = 3;
int G = 2;
int button_1 = 4;
int button_2 = 5;
int button_3 =  6;
int button_enter = 7;
int trig_pin = 8;
int echo_pin = A0;
int userArray[5];
int myArray[5] = {6, 5, 4, 5, 6};
int counter = 0;

void setup() {

  pinMode(door_magnet, OUTPUT);
  pinMode(safe_magnet, OUTPUT);
  pinMode(button_1, INPUT);
  pinMode(button_2, INPUT);
  pinMode(button_3, INPUT);
  pinMode(button_enter, INPUT);
  pinMode(buzzer_pin, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(led_red, OUTPUT);
  pinMode(led_green, OUTPUT);
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);

  Serial.begin(9600);

  digitalWrite(door_magnet, HIGH);
  digitalWrite(safe_magnet, HIGH);

}

void loop() {

  CheckObstacles(trig_pin, echo_pin);
  buttonInput(button_1, button_2, button_3,button_enter);
  checkPassword(led_red, led_green);

}

/******************************************************************************************************************************************
 * Fuctions (Not part of the Loop).
 *****************************************************************************************************************************************/

void dropSafe(int Mysafe_magnet) {

  digitalWrite(Mysafe_magnet, LOW);
  delay(1000);
  digitalWrite(Mysafe_magnet, HIGH);

}

void ringBuzzer(int Mybuzzer_pin) {

  digitalWrite(Mybuzzer_pin, HIGH);
  delay(500);
  digitalWrite(Mybuzzer_pin, LOW);
  delay(500);
  digitalWrite(Mybuzzer_pin, HIGH);
  delay(500);
  digitalWrite(Mybuzzer_pin, LOW);
  delay(500);
  digitalWrite(Mybuzzer_pin, HIGH);
  delay(500);
  digitalWrite(Mybuzzer_pin, LOW);

}

void blink_led(int My_G) {

  digitalWrite(My_G, HIGH);
  delay(300);
  digitalWrite(My_G, LOW);
  delay(300);
  digitalWrite(My_G, HIGH);
  delay(300);
  digitalWrite(My_G, LOW);

}

void buttonInput(int Mybutton_1, int Mybutton_2, int Mybutton_3, int Mybutton_enter) {

  volatile int state_1 = LOW;
  volatile int state_2 = LOW;
  volatile int state_3 = LOW;
  volatile int state_4 = LOW;

  if (digitalRead(Mybutton_1) == LOW && digitalRead(Mybutton_2) == LOW && digitalRead(Mybutton_3) == LOW  && digitalRead(Mybutton_enter) == HIGH) {
    delay(10);
    if (digitalRead(Mybutton_enter) == HIGH)
    {
      while (digitalRead(Mybutton_enter) == HIGH);
      delay(10);
      while (digitalRead(Mybutton_enter) == HIGH);
      state_4 = !state_4;

      dropSafe(safe_magnet);
      ringBuzzer(buzzer_pin);
    }
  }

  if (digitalRead(Mybutton_1) == HIGH && digitalRead(Mybutton_2) == LOW && digitalRead(Mybutton_3) == LOW && digitalRead(Mybutton_enter) == LOW && counter < 5) {
    delay(10);
    if (digitalRead(Mybutton_1) == HIGH)
    {
      while (digitalRead(Mybutton_1) == HIGH);
      delay(10);
      while (digitalRead(Mybutton_1) == HIGH);
      state_1 = !state_1;

      blink_led(G);

      userArray[counter] = 4;
      counter++;
    }
  }

  if (digitalRead(Mybutton_1) == LOW && digitalRead(Mybutton_2) == HIGH && digitalRead(Mybutton_3) == LOW && digitalRead(Mybutton_enter) == LOW && counter < 5) {
    delay(10);
    if (digitalRead(Mybutton_2) == HIGH)
    {
      while (digitalRead(Mybutton_2) == HIGH);
      delay(10);
      while (digitalRead(Mybutton_2) == HIGH);
      state_2 = !state_2;

      blink_led(G);

      userArray[counter] = 5;
      counter++;
    }
  }

  if (digitalRead(Mybutton_1) == LOW && digitalRead(Mybutton_2) == LOW && digitalRead(Mybutton_3) == HIGH && digitalRead(Mybutton_enter) == LOW && counter < 5) {
    delay(10);
    if (digitalRead(Mybutton_3) == HIGH)
    {
      while (digitalRead(Mybutton_3) == HIGH);
      delay(10);
      while (digitalRead(Mybutton_3) == HIGH);
      state_3 = !state_3;

      blink_led(G);

      userArray[counter] = 6;
      counter++;
    }
  }

}

void checkPassword(int Myred_led, int Mygreen_led) {

  if (counter > 4) {
    //checkPass(userArray);


    for (x = 0; x <= 4; x++) {
      if (userArray[x] != myArray[x]) {
        break;
      }
    }
    if (x == 5) {
      //open door
      Serial.println("opening door....");
      digitalWrite(Mygreen_led, HIGH);
      digitalWrite(door_magnet, LOW);
      delay(6000);
      digitalWrite(door_magnet, HIGH);
      digitalWrite(safe_magnet, HIGH);
      digitalWrite(buzzer_pin, LOW);
      delay(2000);
      counter = 0;

    }

    else if (x <= 4) {
      //buzzer
      ringBuzzer;
      digitalWrite(Mygreen_led, LOW);

      digitalWrite(door_magnet, HIGH);
      digitalWrite(safe_magnet, HIGH);
      digitalWrite(buzzer_pin, LOW);
      digitalWrite(Myred_led, HIGH);

      delay(5000);
      counter = 0;
      digitalWrite(Myred_led, LOW);
    }
  }

}
int CheckObstacles(int my_trig_pin, int my_echo_pin) {

  digitalWrite(my_trig_pin, LOW);
  delayMicroseconds(2);

  digitalWrite(my_trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(my_trig_pin, HIGH);

  int duration = pulseIn(my_echo_pin, HIGH);
  int distance = duration * 0.034 / 2;

  if (distance <= 10 && x <= 4) {
    dropSafe;
    ringBuzzer;
    digitalWrite(door_magnet, HIGH);

  }

  else if (distance < 10 && x <= 4) {
    digitalWrite(buzzer_pin, LOW);
    digitalWrite(safe_magnet, HIGH);
    digitalWrite(door_magnet, HIGH);
  }
  return distance;
}
