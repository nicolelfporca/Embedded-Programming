// same dht11 wiring

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DHT.h>

const char* ssid = "Kypen";
const char* password = "Kyr13St3ph3n@";

ESP8266WebServer server(80);

#define DHTPIN 2       // D4 in nodemcu esp8266 pin
#define DHTTYPE DHT11  // DHT 11

DHT dht(DHTPIN, DHTTYPE);

void handleRoot() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  
  String html = "<html><body>";
  html += "<h1>Temperature and Humidity readings:</h1>";
  html += "<p>Temperature: " + String(temperature) + "C</p>";
  html += "<p>Humidity: " + String(humidity) + "%</p>";
  html += "</body></html>";
  
  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for WiFi connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);

  server.begin();
  Serial.println("HTTP server started");
  
  dht.begin();
}

void loop() {
  server.handleClient();
}
