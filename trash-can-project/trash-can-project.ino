// tinkercad: working
// arduino: working

#include <Servo.h>
Servo servo;

int trigger_pin = 2;
int echo_pin = 3;
int time, distance;

void setup(){
 Serial.begin(9600);
 //led
 pinMode(8, OUTPUT);
 pinMode(9, OUTPUT);
 pinMode(10, OUTPUT);
 //ultrasonic distance sensor
 pinMode(trigger_pin, OUTPUT);
 pinMode(echo_pin, INPUT);
 //servo
 servo.attach(7);
}

void loop(){
 digitalWrite(trigger_pin, HIGH);
 delayMicroseconds (10);
 digitalWrite(trigger_pin, LOW);
 time = pulseIn(echo_pin, HIGH);
 distance = (time * 0.034) / 2;
  
 if (distance <= 10){
   printStatus(distance);
   digitalWrite(10,HIGH);
   digitalWrite(9,LOW);
   digitalWrite(8,LOW);
   servo.write(90);
   delay (100);
 }
 else if(distance <= 20){
   printStatus(distance);
   digitalWrite(10,LOW);
   digitalWrite(9,HIGH);
   digitalWrite(8,LOW);
   servo.write(0);
   delay (100);
 }
 else if(distance <= 30){
   printStatus(distance);
   digitalWrite(10,LOW);
   digitalWrite(9,LOW);
   digitalWrite(8,HIGH);
   servo.write(0);
   delay (100);
 }
 else{
   printStatus(distance);
   digitalWrite(10,LOW);
   digitalWrite(9,LOW);
   digitalWrite(8,LOW);
   servo.write(0);
   delay (100);
 }
}

void printStatus(int distance){
  Serial.println("Distance = " + (String) distance + "cm");
}
