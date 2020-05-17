#include <LedControl.h>

int DIN = 10;
int CS =  9;
int CLK = 8;

byte smile[8] = { 0x3C, 0x42, 0xA5, 0x81, 0xA5, 0x99, 0x42, 0x3C };
byte sad[8] = { 0x3C , 0x42, 0xA5, 0x81, 0x99, 0xA5, 0x42, 0x3C };

LedControl lc = LedControl(DIN, CLK, CS, 0);

void setup() {

  lc.shutdown(0, false);
  lc.setIntensity(0, 15);
  lc.clearDisplay(0);// put your setup code here, to run once:

}

void loop() {

  lc.clearDisplay(0);
  printByte(smile);
  delay(1000);
}
