/*
  LiquidCrystal Library
  modified from liquid Crystal example.

  http://www.arduino.cc/en/Tutorial/LiquidCrystal

  Modified for Tacho by https://www.buildcomics.com
*/

#include <LiquidCrystal.h> // include the library code:

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);           // select the pins used on the LCD panel
unsigned long int previousMillis;
const unsigned int interval = 500;

void setup() {
  lcd.begin(16, 2);   // set up the LCD's number of columns and rows:

  //init message:
  lcd.print("I am a HERO!(BC)");
  lcd.setCursor(0, 1);
  lcd.print("Analog reader!");
  delay(2000);

  //clear LCD, set basics
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("A1:     A2:");
  lcd.setCursor(0, 1);
  lcd.print("A3:     A4:");
}

void loop() {
  unsigned long currentMillis = millis();
  unsigned long timeDif = currentMillis - previousMillis;
  if (timeDif >= interval) {
    previousMillis = currentMillis; //reset counter
    unsigned int x;
    
    x = analogRead(A0); //read buttons
    if (x < 60) { //right button
      //lcd.print ("Right");
    }
    else if (x < 200) { //up button
      
    }
    else if (x < 400) { //down button
      
    }
    else if (x < 600) { //left button
      //lcd.print ("Left  ");
    }
    else if (x < 800) { //select = reset button, reset turnCount;
      //turnCount = 0;
    }

    unsigned int a1,a2,a3,a4;
    a1 = analogRead(A1);
    a2 = analogRead(A2);
    a3 = analogRead(A3);
    a4 = analogRead(A4);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("A1:");
    lcd.print(a1);
    lcd.setCursor(9, 0);
    lcd.print("A2:");
    lcd.print(a2);

    lcd.setCursor(0, 1);
    lcd.print("A3:");
    lcd.print(a3);
    lcd.setCursor(9, 1);
    lcd.print("A4:");
    lcd.print(a4);
      
  }
}
