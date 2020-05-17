int trig_pin = 8;
int echo_pin = A0;
int distance;
int duration;

void setup() {
  pinMode(trig_pin,OUTPUT);// put your setup code here, to run once:
  pinMode(echo_pin,INPUT);
  
  Serial.begin(9600);
}

void loop() {
    // put your main code here, to run repeatedly:
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);

  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, HIGH);

  duration = pulseIn(echo_pin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.println(distance);
}
