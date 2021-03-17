#include <WiFiManager.h>
#include <DNSServer.h>

int led_pin = D0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.flush();
  pinMode(led_pin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  WiFiManager wifiManager;
  wifiManager.autoConnect("RS_Sensor_Node");
  Serial.println("Connected to RS_Sensor_Node:)");
  delay(2000);
}
