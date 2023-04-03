const int potentiometerPin = A0;
const int ledPin = 6;
int reading;
// float reading;

void setup() {
  Serial.begin(9600);
  pinMode(potentiometerPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  reading = (255./1023.) * analogRead(potentiometerPin);
  analogWrite(ledPin, (int) reading);
  Serial.println(reading);
  delay(10);
}