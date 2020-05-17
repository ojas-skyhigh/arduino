
int button_pin = 8;
int led_blue = 2;
int led_red = 3;
int led_green = 4;
int buzzer_pin = 9;
int state;

long interval = 120000;

void setup() {
  pinMode(button_pin, INPUT);
  pinMode(led_blue, OUTPUT);
  pinMode(led_green, OUTPUT);

  Serial.begin(9600);
}

void loop() {
/*  state = digitalRead(button_pin);

  if (state == HIGH) {
    while (state == HIGH);
    delay(10);
    while (state == HIGH);
    state = !state;
*/
    delay(interval);
    Serial.println("Green led is now ON");
    digitalWrite(led_green, HIGH);
    
    delay(interval);
    Serial.println("Blue led is now ON");
    digitalWrite(led_blue, HIGH);
    delay(90000);
    
    Serial.println("Buzzer is HIGH");
    digitalWrite(buzzer_pin, HIGH);
    delay(500);
    digitalWrite(buzzer_pin, LOW);
    delay(500);
    Serial.println("Buzzer is HIGH");    
    digitalWrite(buzzer_pin, HIGH);
    delay(500);
    digitalWrite(buzzer_pin, LOW);
    delay(500);
    Serial.println("Buzzer is HIGH");
    digitalWrite(buzzer_pin, HIGH);
    delay(500);
    digitalWrite(buzzer_pin, LOW);
    delay(500);
    Serial.println("Buzzer is HIGH");
    digitalWrite(buzzer_pin, HIGH);
    delay(500);
    digitalWrite(buzzer_pin, LOW);
    delay(25500);

    Serial.println("Red led is now ON");
    digitalWrite(led_red, HIGH);

  }
//}
