// tinkercad: working
// arduino: working

byte const red = 10;
byte const green = 9;
byte const blue = 8;

byte const potentiometer1 = A0;
byte const potentiometer2 = A1;
byte const potentiometer3 = A2;

int potentiometerReading1 = 0;
int potentiometerReading2 = 0;
int potentiometerReading3 = 0;

void setup() {
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  Serial.begin(9600); 
}

void loop() {
  potentiometerReading1 = analogRead(potentiometer1); 
  potentiometerReading2 = analogRead(potentiometer2); 
  potentiometerReading3 = analogRead(potentiometer3); 

  potentiometerReading1 = map(potentiometerReading1,0,1023,0,255);
  potentiometerReading2 = map(potentiometerReading2,0,1023,0,255);
  potentiometerReading3 = map(potentiometerReading3,0,1023,0,255);

  Serial.println(potentiometerReading1);

  analogWrite(red,potentiometerReading1);
  analogWrite(green,potentiometerReading2);
  analogWrite(blue,potentiometerReading3);

  delay(10);
}
