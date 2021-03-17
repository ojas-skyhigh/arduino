
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <DNSServer.h>
#include <WiFiManager.h>

ESP8266WiFiMulti WiFiMulti;
WiFiClient client;

String api_key = "16J4Z3OYC6GUKTPZ";
const char* server = "https://thingspeak.com/channels/1261098/api_keys";
int field_no = 1;
int led_pin = D0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.flush();
  pinMode(led_pin, OUTPUT);
  wificonnect();
}

void loop() {

  int rand_no = random(0, 99);
  POSTsend(rand_no);
}

void wificonnect() {

  WiFiManager wifiManager;
  wifiManager.autoConnect("RS_Sensor_Node");
  Serial.println("Connected to RS Sensor Node:)");
}

void POSTsend(float data) {

  if (client.connect(server, 80)) {

    String postUrl = api_key;
    postUrl += "&field1=";
    //postUrl += field_no;
    //postUrl += "=";
    postUrl += data;
    postUrl += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + api_key + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postUrl.length());
    client.print("\n\n");
    client.print(postUrl);
    delay(1000);

    String line = " ";
    while (client.available()) {
      line = client.readStringUntil('\r');
      Serial.print(line);
    }
  }
  client.stop();
  Serial.println("Waiting...");
  delay(16000);
}
