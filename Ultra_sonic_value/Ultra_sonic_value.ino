#include <LiquidCrystal.h>

const int echo_pin = A0;  
const int trig_pin  = 7; 
int distance;
int duration;
int cm;

LiquidCrystal lcd(4, 6, 10, 11, 12, 13);

void setup()
{
  pinMode(echo_pin, INPUT);
  pinMode(trig_pin,OUTPUT);
  lcd.begin(16, 2);        
  lcd.clear();             
  delay(1000);             
}

void loop(){
  
  lcd.setCursor(0, 0);
  lcd.print("Distance Test"); 

  lcd.setCursor(0, 1);
  lcd.print("Distance: ");
  lcd.print(cm);
  lcd.print(" cm");
  delay(500);

  duration = pulseIn(echo_pin, HIGH);
  distance = duration * 0.034 / 2;

  pinMode(trig_pin, OUTPUT);
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trig_pin, LOW);

}
