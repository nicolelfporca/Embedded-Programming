// activity 2
// tinkercad: working
// arduino: working

const int led1 = 2;
const int led2 = 3;
const int led3 = 4;
const int buzzer = 6;
const int ldr = A0;
int ldrReading = 0;

void setup(){
  Serial.begin(9600);
  pinMode(led1, OUTPUT); 
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop(){
  ldrReading = analogRead(ldr);
  if(ldrReading < 100){
    Serial.println("madilim");
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
  }
  else if(ldrReading < 100 && ldrReading > 200){
    tone(buzzer, 500, 100);
  }
  else if(ldrReading > 200){
    Serial.println("maliwanag");
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
  }
  delay(500);
}
