#include <WiFiManager.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

String url = "http://192.168.1.6/seminar/sensor.php";

//dapat naka private yung wifi
void setup() {
  Serial.begin(9600);
  WiFiManager wm;
  if(wm.autoConnect("Sensor","password")) {
      Serial.println("Connected");
  } 
  else { 
      Serial.println("Connection failed");
  }
}

void loop() {
  // String value = "bobo";
  String value = "baliw";
  String data = "data=" + (String) value;
  sendDataToServer(data);
  delay(5000);
}

void sendDataToServer(String data) {
  Serial.println(data);
  WiFiClient wifiClient;
  HTTPClient http;

  http.begin(wifiClient, url);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpCode = http.POST(data);
  String response = http.getString();
  
  Serial.println(httpCode);
  Serial.println(response);

  http.end();
}


