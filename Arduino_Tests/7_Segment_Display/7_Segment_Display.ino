int AGD = 12;
int C = 13;
int E = A0;


void setup() {
  // put your setup code here, to run once:
  pinMode(AGD,OUTPUT);
  pinMode(C,OUTPUT);
  pinMode(E,OUTPUT);
  Serial.begin(9600);

}

void loop() {
  
  digitalWrite(C,HIGH);
  digitalWrite(AGD,LOW); 
  delay(300);
  digitalWrite(C,LOW);  
  
}
  digitalWrite(AGD,HIGH);
  analogWrite(E,255);
  delay(300);
  digitalWrite(AGD,LOW);
  analogWrite(E,0); 
}
  digitalWrite(AGD,HIGH);   
  digitalWrite(C,HIGH);
  delay(300);
  digitalWrite(AGD,LOW);
  digitalWrite(C,LOW);
}// put your main code here, to run repeatedly:


}
