#include <Keypad.h>
#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

char* password = "7355608";
int position = 0;
const int buzzerPin = 6;
const int ledPin = 13;
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {10, 9, 8, 7}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {A1, A2, A3, A4}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Insert password:");
  lcd.setCursor(0, 1);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  char customKey = customKeypad.getKey();
  if (customKey) {
    Serial.println(customKey);
    lcd.print(customKey);
    if (customKey == '*') //press * to clear the password
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Insert password:");
      lcd.setCursor(0, 1);
    }
    if (customKey == password[position]) {
      position++;
    }
    if (position == 7) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Bomb has been   ");
      lcd.setCursor(0, 1);
      lcd.print("planted!        ");
      delay(1000);
      for(int i = 1000; i > 10; i = i * 0.9){
      tone(buzzerPin, 4000);
      digitalWrite(ledPin, HIGH);
      delay(100);
      noTone(buzzerPin);
      digitalWrite(ledPin, LOW);
      delay(i);
      }
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Terrorists win! ");
    }
  }
}
