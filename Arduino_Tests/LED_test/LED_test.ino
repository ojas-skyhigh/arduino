int led_pin = A1;

void setup() {
  pinMode(led_pin,OUTPUT);// put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
analogWrite(led_pin,1);
delay(2000);
analogWrite(led_pin,LOW);
}
