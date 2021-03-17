
#include <WiFiManager.h>
#include <DNSServer.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

ESP8266WiFiMulti WiFiMulti;

String api_key = "UHDGHZL2CITP6R81";
int field_no = 1;

void setup() {
  Serial.begin(115200);
  Serial.flush();
  wificonnect();
}

void loop() {
  int random_data = random(0, 99);
  GETsend(random_data);
}

void wificonnect() {

  WiFiManager wifiManager;
  wifiManager.autoConnect("RS_Sensor_Node");
  Serial.println("Connected to RS_Sensor_Node :)");
  delay(500);
}

void GETsend(int data) {

  HTTPClient http; //http is the object of class HTTPClient this class defines the method to create and send HTTP requests
  String url =  "http://api.thingspeak.com/update?api_key=";
  url += api_key;
  url += "&field";
  url += field_no;
  url += "=";// Creating HTTP Query/GET Method
  url += data;// passing the parameter to string, this value will reach cloud at field no.
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
  http.end();
  delay(16000);
}
