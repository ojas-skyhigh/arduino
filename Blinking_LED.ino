int led_pin = 2;

void setup() {
  // put your setup code here, to run once:
  pinMode(led_pin, OUTPUT); // Sets pin to either input or output . In our case the LED is an output as it needs to produce light.
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(led_pin, HIGH);// Used to assign power to the pin which is now "HIGH" which gives power ,switching the LED on.
  delay(2000); // Waits for 2 seconds.
  digitalWrite(led_pin, LOW);  // Used to assign power to the pin which is now "LOW" which stops power ,switching the LED off.
  delay(2000); // Waits for 2 seconds.
}

/* Function explanation :
  pinMode is used to set pin to either input or output . In our case the LED is an output as it needs to produce light.
  digitalWrite is used to assign a HIGH or LOW value which means On and Off value respectively.
  delay is used to tell the Arduino to wait and continue the last thing it was doing for the assigned time.
  
