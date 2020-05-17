int alarm_button = 7;
int buzzer = A3;

void setup() {
    pinMode(alarm_button,INPUT);
    pinMode(buzzer,OUTPUT);

}

void loop() {
  
 if(digitalRead(alarm_button) == HIGH){
  
  analogWrite(buzzer,255);
  delay(500);
  analogWrite(buzzer,0);
  delay(100);
  analogWrite(buzzer,255);
  delay(500);
  analogWrite(buzzer,0);
  delay(100);
  analogWrite(buzzer,255);
  delay(500);
  analogWrite(buzzer,0);
} // put your main code here, to run repeatedly:

}
