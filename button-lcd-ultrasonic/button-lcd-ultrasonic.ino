// tinkercad: working
// arduino: working

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

const byte trigger_pin = 2;
const byte echo_pin = 3;
const byte button = 4;
int time, distance;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup(){
  lcd.begin(0,0);
  lcd.backlight();
  //ultrasonic
  pinMode(trigger_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  //button
  pinMode(button, INPUT);
}

void loop(){
  int buttonStatus = digitalRead(button);
  digitalWrite(trigger_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_pin, LOW);
  time = pulseIn(echo_pin,HIGH);
  distance = (time * 0.034)/2;

  if (buttonStatus == HIGH) {
    lcd.clear();
    lcd.print(distance);
    lcd.print("cm");
    delay(1000);
  }else{
    lcd.clear();
  }
}
