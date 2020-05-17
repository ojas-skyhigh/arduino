
#include <IRremote.h>

int RECV_PIN = 11;
int led_pin = 2;

IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  pinMode(led_pin,OUTPUT);
  Serial.begin(9600); 
  irrecv.enableIRIn(); 
} 

void loop() {
  
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    Serial.println(" ");
    irrecv.resume(); 
  }
}
