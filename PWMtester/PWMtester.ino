/*
  LiquidCrystal Library
  modified from liquid Crystal example.

  http://www.arduino.cc/en/Tutorial/LiquidCrystal

  Modified for Tacho by https://www.buildcomics.com
*/

#include <LiquidCrystal.h> // include the library code:

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);           // select the pins used on the LCD panel
unsigned long int previousMillis;
const unsigned int interval = 100;
unsigned int pwmVal;

void setup() {
  lcd.begin(16, 2);   // set up the LCD's number of columns and rows:
  pwmVal = 100;

  //setup timer:
  TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM20); //non-inverting phase correct 8bit pwm, enable a/b
  TCCR2B = _BV(CS20); //no prescaler (30khz)*/
  OCR2A = 0; //pin 15 D11
  pinMode(11, OUTPUT); //OC2A output is D11


  //init message:
  lcd.print("I am a HERO!(BC)");
  lcd.setCursor(0, 1);
  lcd.print("PWM tester!");
  delay(2000);

  //clear LCD, set basics
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("PWM Testing...");
}

void loop() {
  unsigned long currentMillis = millis();
  unsigned long timeDif = currentMillis - previousMillis;
  if (timeDif >= interval) {
    previousMillis = currentMillis; //reset counter
    unsigned int x;

    x = analogRead(A0); //read buttons
    if (x < 60) { //right button
      if (pwmVal < 245) {
        pwmVal += 10;
      }
    }
    else if (x < 200) { //up button
      if (pwmVal < 255) {
        pwmVal++;
      }
    }
    else if (x < 400) { //down button
      if (pwmVal >= 1) {
        pwmVal--;
      }
    }
    else if (x < 600) { //left button
      if (pwmVal >= 10) {
        pwmVal -= 10;
      }
    }
    else if (x < 800) { //select = reset button, reset turnCount;
      //turnCount = 0;
    }

    lcd.setCursor(0, 1);
    lcd.print("PWMVAL: ");
    lcd.print(pwmVal);
    lcd.print("  "); //clear excess characters
    OCR2A = pwmVal;


  }
}
