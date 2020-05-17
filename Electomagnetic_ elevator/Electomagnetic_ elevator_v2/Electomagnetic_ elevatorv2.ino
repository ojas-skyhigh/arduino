/*
 * Created by Ojas Patil of VII A
 * GNS 
 * For Science Day on 28/2/2020
 */
int floor_1_button = 5;
int floor_2_button= 4;
int floor_3_button = 3;
int alarm_button = 2;
int door_magnet = 9;
int buzzer = 10;
int floor_2_motor_down = 11;
int AGD = 12;
int C = 13;
int E = A0;

int floor_1_magnet = A1;
int floor_1_reverse_magnet = A2;
int floor_3_magnet = A3;
int floor_3_reverse_magnet = A4;

volatile int state_1 = LOW;
volatile int state_2 = LOW;
volatile int state_3 = LOW;

void setup() {

  pinMode(floor_1_button,INPUT);
  pinMode(floor_2_button,INPUT);
  pinMode(floor_3_button,INPUT);
  pinMode(alarm_button,INPUT);
  pinMode(door_magnet,OUTPUT);
  pinMode(floor_1_magnet,OUTPUT);
  pinMode(floor_2_motor_down,OUTPUT);
  pinMode(floor_3_magnet,OUTPUT);
  pinMode(floor_3_reverse_magnet,OUTPUT);
  pinMode(floor_1_reverse_magnet,OUTPUT); 
  pinMode(buzzer,OUTPUT);
  pinMode(AGD,OUTPUT);
  pinMode(C,OUTPUT);
  pinMode(E,OUTPUT);

}

void loop() {

  digitalWrite(C,HIGH);

  digitalWrite(AGD,HIGH); 
  analogWrite(E,255);

if(digitalRead(floor_1_button)==HIGH && digitalRead(floor_2_button) == LOW && digitalRead(floor_3_button) == LOW){       
      delay(10);                        
      if(digitalRead(floor_1_button)==HIGH)      
      {     
        while(digitalRead(floor_1_button)==HIGH);
        delay(10);                      
        while(digitalRead(floor_1_button)==HIGH);
        state_1 = !state_1; 

  digitalWrite(floor_2_motor_down,HIGH);
  delay(30);
  digitalWrite(floor_2_motor_down,LOW);
  
  digitalWrite(door_magnet,LOW);
  delay(200);
  digitalWrite(floor_1_magnet,LOW);
  digitalWrite(floor_3_magnet,LOW);
  digitalWrite(floor_3_reverse_magnet,LOW); 
  digitalWrite(floor_2_motor_down,LOW);
  delay(50);
  digitalWrite(floor_1_reverse_magnet,HIGH);
  delayMicroseconds(100);
  digitalWrite(floor_1_reverse_magnet,LOW);
  delay(500);
  digitalWrite(door_magnet,HIGH);
  delay(200);
  digitalWrite(floor_1_magnet,LOW);
      } 
}

else if(digitalRead(floor_1_button)==LOW && digitalRead(floor_2_button) == HIGH && digitalRead(floor_3_button) == LOW){       
      delay(10);                        
      if(digitalRead(floor_2_button)==HIGH)      
      {     
        while(digitalRead(floor_2_button)==HIGH);
        delay(10);                      
        while(digitalRead(floor_2_button)==HIGH);
        state_2= !state_2;

 //if(digitalRead(led_1) == HIGH){
  
  digitalWrite(floor_2_motor_down,HIGH);
  delay(30);
  digitalWrite(floor_2_motor_down,LOW); 
        
  digitalWrite(door_magnet,LOW);
  delay(200);  
  digitalWrite(floor_1_magnet,LOW);
  digitalWrite(floor_1_reverse_magnet,HIGH);
  digitalWrite(floor_3_magnet,HIGH);
  digitalWrite(floor_3_reverse_magnet,LOW);
  delay(70);
  digitalWrite(floor_2_motor_down,HIGH);
  delay(10); 
  digitalWrite(floor_2_motor_down,LOW);
  digitalWrite(floor_1_reverse_magnet,LOW);
  digitalWrite(floor_3_magnet,LOW);
    delay(200);
  digitalWrite(door_magnet,HIGH);
     // }
//else if(digitalRead(led_3) == HIGH){
  
  digitalWrite(floor_2_motor_down,HIGH);
  delay(30);
  digitalWrite(floor_2_motor_down,LOW);

  digitalWrite(door_magnet,LOW);
  delay(200);
  digitalWrite(floor_3_magnet,LOW);
  digitalWrite(floor_1_magnet,LOW);
  digitalWrite(floor_1_reverse_magnet,LOW);
  digitalWrite(floor_3_reverse_magnet,LOW);
  delay(100);
  digitalWrite(floor_2_motor_down,HIGH);
  delay(10); 
  digitalWrite(floor_2_motor_down,LOW);
  
 //}
  
 }


else if(digitalRead(floor_1_button)==LOW && digitalRead(floor_2_button) == LOW && digitalRead(floor_3_button) == HIGH){       
      delay(10);                        
      if(digitalRead(floor_1_button)==HIGH)      
      {     
        while(digitalRead(floor_1_button)==HIGH);
        delay(10);                      
        while(digitalRead(floor_1_button)==HIGH);
        state_3 = !state_3;
         
  digitalWrite(floor_2_motor_down,HIGH);
  delay(30);
  digitalWrite(floor_2_motor_down,LOW);
  
  digitalWrite(door_magnet,LOW);
  delay(500);
  digitalWrite(floor_1_magnet,LOW);
  digitalWrite(floor_1_reverse_magnet,HIGH);
  digitalWrite(floor_3_magnet,HIGH);
  digitalWrite(floor_2_motor_down,LOW);
  delay(100);
  digitalWrite(floor_3_magnet,LOW);
  digitalWrite(floor_3_reverse_magnet,HIGH);
  delayMicroseconds(10);
  digitalWrite(floor_3_reverse_magnet,LOW);
  digitalWrite(floor_3_magnet,HIGH);
  delay(500);
  digitalWrite(door_magnet,HIGH);
  digitalWrite(floor_3_magnet,LOW);
      }
}

else if(digitalRead(alarm_button) == HIGH){
  
  digitalWrite(buzzer,HIGH);
  delay(500);
  digitalWrite(buzzer,LOW);
  delay(500);
  digitalWrite(buzzer,HIGH);
  delay(500);
  digitalWrite(buzzer,LOW);
  delay(500);
  digitalWrite(buzzer,HIGH);
  delay(500);
  digitalWrite(buzzer,LOW);
}
}
}
