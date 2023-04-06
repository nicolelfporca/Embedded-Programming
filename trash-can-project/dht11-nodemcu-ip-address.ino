// same dht11 wiring

const int refresh = 3;  //3 seconds

// DHT11
#include "DHT.h"
#define DHTPIN 2  // digital pin = D4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
float tValue;

// NODEMCU ESP8266
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#ifndef STASSID
#define STASSID "SanaAllMayWifi"  //Your WiFi SSID
#define STAPSK "banada2020"       //Your WiFi Password
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

ESP8266WebServer server(80);

void sendTemp() {
  String page = "<!DOCTYPE html>\n\n";
  page += "<meta http-equiv='refresh' content='";
  page += String(refresh);  //how often temperature is read
  page += "'/>\n";
  page += "<html>\n";
  page += "<body>\n";
  page += "<p style=\"font-size:50px;\">Temperature<br/>\n";
  page += "<p style=\"color:red; font-size:50px;\">";
  page += String(tValue, 2);
  page += " C </p>\n";
  page += "</body>\n";
  page += "</html>\n";
  server.send(200, "text/html", page);
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void setup(void) {
  dht.begin();
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  if (WiFi.status() == WL_CONNECTED) {
    uint8_t macAddr[6];
    WiFi.macAddress(macAddr);
    Serial.printf("Connected, mac address: %02x:%02x:%02x:%02x:%02x:%02x\n", macAddr[0], macAddr[1], macAddr[2], macAddr[3], macAddr[4], macAddr[5]);
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("robojaxDHT")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", sendTemp);

  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  MDNS.update();
  float celcius = dht.readTemperature();
  float humidity = dht.readHumidity();
  float farenheit = dht.readTemperature(true);
  Serial.println((String)celcius + " C ");
  tValue = celcius;
  delay(300);  // change this to larger value (1000 or more) if you don't need very often reading
}
