/*
   Created by Learning To Be A Maker
*/

int button_pin = 2; // Pin where button is to be connected.
int led_pin = 13; // Pin where LED is to be connected.

volatile int button_state = LOW; // The state of the button is to be mentioned as LOW or else it will always give a HIGH value.

void setup() {
  pinMode(led_pin, OUTPUT); // Sets pin to either input or output. In our case the LED is an output as it needs to produce light.
  pinMode(button_pin, INPUT); // // Sets pin to either input or output. In our case the button is an output as it needs to return a value.
}

void loop() {

  button_state = digitalRead(button_pin); // The digitalRead function is used to read from a given pin. In our case, button_pin (pin 2) and store it in a varieble

  if (digitalRead(button_pin) == HIGH) { // Check if button_pin's state is HIGH.
    delay(10);                           // delay to prevent overwrite of values.
    if (digitalRead(button_pin) == HIGH) { // Check again if button_pin's state is still HIGH...

      while (digitalRead(button_pin) == HIGH); // while it is HIGH...
      delay(10);                               // one more delay to prevent overwrite of values.
      while (digitalRead(button_pin) == HIGH); // Check again if it is still HIGH ...
      button_state = !button_state;
      // When button_state is HIGH, do something. In our case, switch on an LED
      digitalWrite(led_pin, button_state); // Now give power to LED according to button_state
    }
  }
}
