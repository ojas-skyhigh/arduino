
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <DNSServer.h>
#include <WiFiManager.h>

ESP8266WiFiMulti WiFiMulti;
WiFiClient client;

String api_key = "16J4Z3OYC6GUKTPZ";
const char*  server = "api.thingspeak.com";
int field_no = 1;
int led_pin = D0;
int temp_pin = A0;

void setup() {

  Serial.begin(115200);
  Serial.flush();
  pinMode(led_pin, OUTPUT);
  pinMode(temp_pin, INPUT);
  wificonnect();
}

void loop() {

  float temperature = readTemp(temp_pin);
  POSTsend(temperature);
}

void wificonnect() {

  WiFiManager wifiManager;
  wifiManager.autoConnect("RS_Sensor_Node");
  Serial.println("Connected to RS Sensor Node:)");
}

int readTemp(int My_temp_pin) {

  float sensor_val = analogRead(temp_pin);
  float voltage_mv = sensor_val * 3100 / 1024;
  float temperature = voltage_mv / 10;
  return temperature;
}

void POSTsend(float data) {

  if (client.connect(server, 80)) {

    String postUrl = api_key;
    postUrl += "&field";
    postUrl += field_no;
    postUrl += "=";
    postUrl += data;
    postUrl += "r\n\r\n";

    client.print("POST /update HTTPS/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("User-Language: en/us");
    client.print("X-THINGSPEAKAPIKEY: " + api_key + "\n");
    client.print("Content-Type application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postUrl.length());
    client.print("\n\n");
    client.print(postUrl);
    delay(1000);

    String line = " ";
    while (client.available()) {
      line = client.readStringUntil('\r');
      Serial.println(line);
    }
  }
  client.stop();
  Serial.println("Waiting...");
  delay(16000);

}
