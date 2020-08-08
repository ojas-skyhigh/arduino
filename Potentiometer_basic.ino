/*
 * Created by 'Learning To Be  Maker'.
 */

int led_pin = 3; // Pin where we have to connect the LED
int pot_pin = A0; // Pin where we should connect the potentiometer
int potVal; // Value returned from the pot on twisting it

void setup() {

  pinMode(led_pin,OUTPUT); // Set the LED as OUTPUT as we need it to OUTPUT a light
  pinMode(pot_pin, INPUT); // Set the pot as INPUT as we need the values FROM the pot
}

void loop() {

potVal = analogRead(pot_pin); // The values returned from pot_pin are to be read and stored as an integer potVal

digitalWrite(led_pin,potVal);
}
