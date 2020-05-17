int motor = 11;
int button_pin = 2;
int state_1;

void setup() {
 pinMode(motor,OUTPUT);
 pinMode(button_pin,INPUT);
}

void loop() {
 
if(digitalRead(button_pin)==HIGH){       
      delay(10);                        
      if(digitalRead(button_pin)==HIGH)      
      {     
        while(digitalRead(button_pin)==HIGH);
        delay(10);                      
        while(digitalRead(button_pin)==HIGH);
        state_1 = !state_1; 
        
digitalWrite(motor,HIGH);

}
}

if(digitalRead(button_pin)==LOW){       
      delay(10);                        
      if(digitalRead(button_pin)==LOW)      
      {     
        while(digitalRead(button_pin)==LOW);
        delay(10);                      
        while(digitalRead(button_pin)==LOW);
        state_1 = !state_1; 
        
digitalWrite(motor,LOW);

}
}
}
