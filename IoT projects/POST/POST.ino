/*
  Problem Statement: Upload LM35 Sensor Data to your channel on ThingSpeak.com using POST HTTP Method
  Developed by: Rahul Shrivastava
*********************************
  Pin Connections
  LM35    NODEMCU
  Vcc(1)   3.3V
  GND(3)   GND
  OUT(2)   A0
*********************************
*/

#include <Arduino.h>//
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <DNSServer.h>
#include <WiFiManager.h>

WiFiClient client;

String apiKey = "16J4Z3OYC6GUKTPZ";     //  Enter your Write API key from ThingSpeak
const char* server = "api.thingspeak.com";
int sensor = A0;

void setup()
{
  Serial.begin(115200);
  delay(10);
  Serial.flush();
  wificonnect();
}

void loop()
{
  int random_data = random(0, 99);
  POSTSend(random_data);
}

void wificonnect()
{
  WiFiManager wifiManager;
  wifiManager.autoConnect("RS_Sensor_Node");
  Serial.println("connected to RS_Sensor_Node:)");
}

void POSTSend(float data)
{
  if (client.connect(server, 80))
  {
    //"xxvcbcb&field2=21"
    String postStr = apiKey;
    postStr += "&field1=";
    postStr += data;
    postStr += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
    delay(1000);
    String line = "";
    while (client.available())
    {
      line = client.readStringUntil('\r');
      Serial.print(line);
    }
  }
  client.stop();
  Serial.println("Waiting...");
  delay(16000);
}
