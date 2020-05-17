/*char data = 0;
int led = 8;

void setup() {
  pinMode(led, OUTPUT); // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {

    data = Serial.read();
    Serial.print(data);
    Serial.print("\n");

    if (data == "0") {
      digitalWrite(led, LOW);
    }
    else if (data == "1") {
      digitalWrite(led, HIGH);
    }
  }
}
*/
#include <SoftwareSerial.h>
#define LED_PIN 13

SoftwareSerial mySerial(7, 8);  

void setup() {  
  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop() {  
  int c;
  
  if (mySerial.available()) {
    c = mySerial.read();  
    Serial.println("Got input:");
    if (c != 0)
    {
      Serial.println("  on");
      digitalWrite(LED_PIN, HIGH);
    }
    else
    {
      Serial.println("  off");
      digitalWrite(LED_PIN, LOW);
    }  
  }
}
