// activity 4
// tinkercad: not tried yet
// arduino: working

// LCD
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

// DHT11
#include "DHT.h"
#define DHTPIN 5
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// MQ2
#define MQ2pin A0
float sensorValue;  //variable to store sensor value

// PIR
const byte sensorPin = 3;
int sensor = 0;

void setup() {
	dht.begin(); // initialize dht
	Serial.begin(9600);
  // LCD
  lcd.begin();
	lcd.backlight();
  // PIR
  pinMode(sensorPin, INPUT);
}

void loop(){
  // comments others to demonstrate
  pir();
  mq2();
  humidity();
}

void pir(){
  sensor = digitalRead(sensorPin);  
  if(sensor==HIGH){
    lcd.clear();
    lcd.print("Motion detected!");
    delay(100);
  }
  else{
    lcd.clear();
    lcd.print("No motion detected!");
    delay(100);
  }
}

void mq2(){
  sensorValue = analogRead(MQ2pin); // read analog input pin 0
  lcd.clear();
	lcd.print("SensorVal: ");
	lcd.print(sensorValue);
	delay(2000); // wait 2s for next reading
}

void humidity(){
  delay(1000);
    
  float h = dht.readHumidity();
  float f = dht.readTemperature(); // fareheit
  float t = dht.readTemperature(true); // celcius

    // Check if any reads failed and exit early
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.print("Failed to read from DHT sensor!");
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("HD:"+ (String) h + "%"); // humidity
  lcd.setCursor(0, 1);
  lcd.print("TP:"+ (String) t +"F|"+ (String) f +"C"); //temperature
}