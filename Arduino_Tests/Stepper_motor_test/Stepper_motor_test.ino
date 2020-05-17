
int _step = 512; // Each step = 0.7 degree
int _speed = 1;
int Pin0 = 9;
int Pin1 = 10;
int Pin2 = 11;
int Pin3 = 12;

void setup() {

  pinMode(Pin0, OUTPUT);
  pinMode(Pin1, OUTPUT);
  pinMode(Pin2, OUTPUT);
  pinMode(Pin3, OUTPUT);
}

void loop() {

Speed(0);//Enter required speed here (from 0-20)
Step(0);//Enter the movement required here (from 0-512 ,where 512 = 360 degrees) use minus(-) for counter-clockwise movement.
}
void Speed(int stepperspeed)//set Stepper speed
{
  _speed = 15 - stepperspeed;
  if ( _speed < 1) {
    _speed = 1;
  }
  if ( _speed > 15) {
    _speed = 15;
  }
}

void Step(int _step)//Stepper motor rotation
{
  if (_step >= 0) { // Stepper motor forward
    for (int i = 0; i < _step; i++) {
      setStep(1, 0, 0, 1);
      delay(_speed);
      setStep(1, 0, 0, 0);
      delay(_speed);
      setStep(1, 1, 0, 0);
      delay(_speed);
      setStep(0, 1, 0, 0);
      delay(_speed);
      setStep(0, 1, 1, 0);
      delay(_speed);
      setStep(0, 0, 1, 0);
      delay(_speed);
      setStep(0, 0, 1, 1);
      delay(_speed);
      setStep(0, 0, 0, 1);
      delay(_speed);
    }
  } else { // Stepper motor backward
    for (int i = _step; i < 0; i++) {
      setStep(0, 0, 0, 1);
      delay(_speed);
      setStep(0, 0, 1, 1);
      delay(_speed);
      setStep(0, 0, 1, 0);
      delay(_speed);
      setStep(0, 1, 1, 0);
      delay(_speed);
      setStep(0, 1, 0, 0);
      delay(_speed);
      setStep(1, 1, 0, 0);
      delay(_speed);
      setStep(1, 0, 0, 0);
      delay(_speed);
      setStep(1, 0, 0, 1);
      delay(_speed);
    }
  }
}
void setStep(int a, int b, int c, int d)
{
  digitalWrite(Pin0, a);
  digitalWrite(Pin1, b);
  digitalWrite(Pin2, c);
  digitalWrite(Pin3, d);
}
