// tinkercad: not working
// arduino: working

byte pin[] = {2,3,4,5,6,7,8,9};
int number[10][8]= {
    // {E, D, C, DP, B, A, F, G}
    {1,1,1,0,1,1,1,0},//0
    {0,0,1,0,1,0,0,0},//1
    {1,1,0,0,1,1,0,1},//2
    {0,1,1,0,1,1,0,1},//3
    {0,0,1,0,1,0,1,1},//4
    {0,1,1,0,0,1,1,1},//5
    {1,1,1,0,0,1,1,1},//6
    {0,0,1,0,1,1,0,0},//7
    {1,1,1,0,1,1,1,1},//8
    {0,1,1,0,1,1,1,1},//9
  };

void setup() {
  for(byte a=0; a<8; a++){
    pinMode(pin[a], OUTPUT);
  }
}

void loop() {
  for(int a=0; a<10; a++){
    for(int b=0; b<8; b++){
      digitalWrite(pin[b], number[a][b]);
    }
    delay(500); 
  } 
}
