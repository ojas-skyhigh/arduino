
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <DNSServer.h>
#include <WiFiManager.h>

ESP8266WiFiMulti WiFiMulti;

String api_key = "16J4Z3OYC6GUKTPZ";
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
  GETsend(temperature);
}

void wificonnect() {

   WiFiManager wifiManager;
   wifiManager.autoConnect("RS_Sensor_Node");
   Serial.println("Connected to RS Sensor Node:)");
}

int readTemp(int My_temp_pin) {

  float sensor_val = analogRead(temp_pin);
  float voltage_mv = sensor_val * 3.3 * 1000 / 1023;
  float temperature = voltage_mv / 10;
  return temperature;
}

void GETsend(float data) {
  HTTPClient http; //http is the object of class HTTPClient this class defines the method to create and send HTTP requests
  String url =  "http://api.thingspeak.com/update?api_key=";
  url += api_key;
  url += "&field";
  url += field_no;
  url += "=";// Creating HTTP Query/GET Method
  url += data;// passing the parameter to string, this value will reach cloud at field1
  http.begin(url);// initiate HTTP Request to establish connection

  Serial.print("HTTP REQUEST SENT, Waiting for response\n");

  // start connection and send HTTP header
  int httpCode = http.GET();// get method, returns a http code, -ve if access denied
  // httpCode will be negative on error
  if (httpCode > 0) {
    // HTTP header has been send and Server response header has been handled
    Serial.printf("Sensor data uploaded sucessfully");
  }
  else
  {
    Serial.printf("Failed to connect to server");
  }
  digitalWrite(led_pin, HIGH);
  delay(500);
  digitalWrite(led_pin, LOW);
  delay(500);
  digitalWrite(led_pin, HIGH);
  delay(500);
  digitalWrite(led_pin, LOW);
  http.end();
  delay(16000);
}
