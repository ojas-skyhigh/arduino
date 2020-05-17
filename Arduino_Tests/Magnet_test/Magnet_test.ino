int magnet_1 = A1;
int magnet_2 = A2;

void setup() {
   pinMode(magnet_1,OUTPUT);
   pinMode(magnet_2,OUTPUT);

}

void loop() {
   digitalWrite(magnet_1,HIGH);
   digitalWrite(magnet_2,LOW);   

}
