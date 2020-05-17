int button_pin = 6;
int led_pin = 13;

volatile int buttonState = LOW;

void setup() {
  pinMode(led_pin, OUTPUT);
  pinMode(button_pin, INPUT);
  Serial.begin(9600);
}

void loop() {

  buttonState = digitalRead(button_pin);

  if (digitalRead(button_pin) == HIGH) {
    delay(10);
    if (digitalRead(button_pin) == HIGH) {

      while (digitalRead(button_pin) == HIGH);
      delay(10);
      while (digitalRead(button_pin) == HIGH);
      buttonState = !buttonState;

      Serial.println("On");
      digitalWrite(led_pin, HIGH);
    }
  }

  else if (digitalRead(button_pin) == LOW) {
    Serial.println("Off");
    digitalWrite(led_pin, LOW);
  }
}
