#include<Keypad.h>
#include<Adafruit_LiquidCrystal.h>
#include<Wire.h>

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', '+'},
  {'4', '5', '6', '-'},
  {'7', '8', '9', 'C'},
  {'*', '0', '=', '/'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

// Created instances
Keypad myKeypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
Adafruit_LiquidCrystal lcd_1(0);

boolean firstNumState = true;
String firstNum = "";
String secondNum = "";
float result = 0.0;
char operatr = ' ';

void setup() {
  lcd_1.begin(0,0);
  lcd_1.setCursor(0, 0);
  lcd_1.print("Arduino Calculator");
  lcd_1.setCursor(0, 1);
  lcd_1.print("by MakerPro");
  delay(1000);
  scrollDisplay();
  clr();
}

void loop() {
  char newKey = myKeypad.getKey();
  if (newKey != NO_KEY && (newKey == '1' || newKey == '2' || newKey == '3' || newKey == '4' || newKey == '5' || newKey == '6' || newKey == '7' || newKey == '8' || newKey == '9' || newKey == '0')) {
    if (firstNumState == true) {
      firstNum = firstNum + newKey;
      lcd_1.print(newKey);
    }
    else {
      secondNum = secondNum + newKey;
      lcd_1.print(newKey);
    }
  }
  if (newKey != NO_KEY && (newKey == '+' || newKey == '-' || newKey == '*' || newKey == '/')) {
    if (firstNumState == true) {
      operatr = newKey;
      firstNumState = false;
      lcd_1.setCursor(15, 0);
      lcd_1.print(operatr);
      lcd_1.setCursor(5, 1);
    }
  }
  if (newKey != NO_KEY && newKey == '=') {
    if (operatr == '+') {
      result = firstNum.toFloat() + secondNum.toFloat();
    }
    if (operatr == '-') {
      result = firstNum.toFloat() - secondNum.toFloat();
    }
    if (operatr == '*') {
      result = firstNum.toFloat() * secondNum.toFloat();
    }
    if (operatr == '/') {
      result = firstNum.toFloat() / secondNum.toFloat();
    }
    lcd_1.clear();
    lcd_1.setCursor(0, 0);
    lcd_1.print(firstNum);
    lcd_1.print(operatr);
    lcd_1.print(secondNum);
    lcd_1.setCursor(0, 1);
    lcd_1.print("=");
    lcd_1.print(result);
    firstNumState = true;
  }
  if (newKey != NO_KEY && newKey == 'C') {
    clr();
  }
}

void scrollDisplay() {
  // scroll 13 positions (string length) to the left
  // to move it offscreen left:
  for (int positionCounter = 0; positionCounter < 3; positionCounter++) {
    // scroll one position left:
    lcd_1.scrollDisplayLeft();
    // wait a bit:
    delay(300);
  }
  delay(1000);

  // scroll 29 positions (string length + display length) to the right
  // to move it offscreen right:
  for (int positionCounter = 0; positionCounter < 3; positionCounter++) {
    // scroll one position right:
    lcd_1.scrollDisplayRight();
    // wait a bit:
    delay(300);
  }
  delay(2000);
}

void clr() {
  lcd_1.clear();
  lcd_1.setCursor(0, 0);
  lcd_1.print("1st: ");
  lcd_1.setCursor(12, 0);
  lcd_1.print("op ");
  lcd_1.setCursor(0, 1);
  lcd_1.print("2nd: ");
  lcd_1.setCursor(5, 0);
  firstNum = "";
  secondNum = "";
  result = 0;
  operatr = ' ';
}