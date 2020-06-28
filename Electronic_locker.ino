
int led_pin = 2;
int red_led = 3;
int potentiometer = A1;
int buzzer_pin = 7;
int magnet = 8;
int counter;

void setup() {
  // put your setup code here, to run once:
  pinMode(led_pin, OUTPUT);
  pinMode(red_led, OUTPUT);
  pinMode(potentiometer, INPUT);
  pinMode(magnet, OUTPUT);
  pinMode(buzzer_pin, OUTPUT);

  Serial.begin(9600);
  digitalWrite(magnet, HIGH);
}

void loop() {

  Serial.println(readDegree(potentiometer));
  counter = 0;

  if (readDegree(potentiometer) <= 50) {
    counter++;
    delay(2000);
    pass(led_pin, buzzer_pin);
    delay(5000);
    readDegree(potentiometer);

    if (readDegree(potentiometer) <= 823 && readDegree(potentiometer) >= 680) {
      counter++;
      pass(led_pin, buzzer_pin);
      delay(5000);
      readDegree(potentiometer);
      Serial.println(readDegree(potentiometer));

      if (readDegree(potentiometer) <= 1023 && readDegree(potentiometer) >= 1010) {
        counter++;
        pass(led_pin, buzzer_pin);
        delay(5000);
        readDegree(potentiometer);

        if (readDegree(potentiometer) <= 365 && readDegree(potentiometer) >= 187) {
          counter++;
          pass(led_pin, buzzer_pin);
          readDegree(potentiometer);
        }

        else if (readDegree(potentiometer) != 0) {
          noPass(buzzer_pin);

        }

      }

      else if (readDegree(potentiometer) != 0) {
        noPass(buzzer_pin);
      }

    }

    else if (readDegree(potentiometer) != 0) {
      noPass(buzzer_pin);
    }

    if (counter == 4) {
      finalPass(led_pin, buzzer_pin);
    }
  }
}

int readDegree(int My_potentio_meter) {

  int degree = analogRead(My_potentio_meter);
  Serial.println(degree);
  return degree;
}

void pass(int My_led_pin, int My_buzzer_pin) {

  digitalWrite(My_led_pin, HIGH);
  delay(1000);
  digitalWrite(My_led_pin, LOW);
  digitalWrite(magnet, HIGH);
}

void noPass(int My_buzzer_pin) {

  digitalWrite(red_led, HIGH);
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
  digitalWrite(red_led, LOW);
  digitalWrite(magnet, HIGH);
  delay(7000);
}

void finalPass(int My_led_pin, int My_buzzer_pin) {

  digitalWrite(My_led_pin, HIGH);
  digitalWrite(My_buzzer_pin, HIGH);
  delay(200);
  digitalWrite(My_led_pin, LOW);
  digitalWrite(My_buzzer_pin, LOW);
  delay(200);
  digitalWrite(My_led_pin, HIGH);
  digitalWrite(My_buzzer_pin, HIGH);
  delay(200);
  digitalWrite(My_led_pin, LOW);
  digitalWrite(My_buzzer_pin, LOW);
  delay(200);
  digitalWrite(My_led_pin, HIGH);
  digitalWrite(My_buzzer_pin, HIGH);
  delay(200);
  digitalWrite(My_led_pin, LOW);
  digitalWrite(My_buzzer_pin, LOW);
  delay(200);
  digitalWrite(My_led_pin, HIGH);
  digitalWrite(My_buzzer_pin, HIGH);

  digitalWrite(My_led_pin, LOW);
  digitalWrite(My_buzzer_pin, LOW);
  digitalWrite(magnet, LOW);
  delay(10000);
  digitalWrite(magnet, HIGH);
}
