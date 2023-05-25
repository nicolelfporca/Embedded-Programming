//PICC - Proximity Integrated Circuit Card
//UID - Unique IDentifier number set by factory on each PICC (bytes 0..6 of memory block 0) may be be 4-10 bytes.
//SAK - Select acknowledge

// RFID
#include <SPI.h>
#include <MFRC522.h>
MFRC522 mfrc522(SS_PIN, RST_PIN);
String id = "04 99 63 2B";
// LCD
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
// SERVO
#include <Servo.h>

// RFID
#define SS_PIN 10
#define RST_PIN 9
// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);
// SERVO
Servo servo;
// LED
const byte buzzer = 4;
const byte green = 7;
const byte red = 6;

void setup() {
  Serial.begin(9600);
  // RFID
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Tap your card to login..");
  // LCD
  lcd.begin();
  lcd.backlight();
  lcd.print("Tap your card  ");
  // SERVO
  servo.write(0);
  servo.attach(2); 
  // LED
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);
  // BUZZER
  pinMode(buzzer, OUTPUT);
}

void loop() {
  // Llook for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  // select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) // returns 1 if that card's UID can be read
  {
    return;
  }
  // Serial.print(F("RFID Tag UID : "));
  String UID = getRfidUID(mfrc522.uid.size);
  Serial.println(UID);
  lcd.clear();
  if(UID == " E2 C6 47 19"){
    lcd.print("GRANTED");
    tone(buzzer, 800, 500);
    digitalWrite(green,HIGH);
    digitalWrite(red,LOW);
    servo.write(90);
  }
  else{
    lcd.print("DENIED");
    tone(buzzer, 100, 500);
    digitalWrite(green,LOW);
    digitalWrite(red,HIGH);
  }
  delay(2000);
  digitalWrite(green,LOW);
  digitalWrite(red,LOW);
  servo.write(0);
  lcd.clear();
  lcd.print("Tap your card");
  mfrc522.PICC_HaltA(); // this call must be made to prevent repeated re-detection of our card

 }
  // extract UID from mfrc522 class variable
  String getRfidUID(byte bufferSize) {
  String sUID = "";
  for (byte i = 0; i < bufferSize; i++) {
    sUID.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ")); 
    sUID.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  sUID.toUpperCase();
  return sUID;
}