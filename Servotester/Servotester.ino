/*
  LiquidCrystal Library
  modified from liquid Crystal example.

  http://www.arduino.cc/en/Tutorial/LiquidCrystal

  Modified for Servo by https://www.buildcomics.com
*/
#define SERVOPIN 11

#include <LiquidCrystal.h> // include the library code for the display


LiquidCrystal lcd(8, 9, 4, 5, 6, 7);           // select the pins used on the LCD panel
unsigned long int previousMillis;
const unsigned int interval = 100;
unsigned int pwmVal;


void setup() {
  lcd.begin(16, 2);   // set up the LCD's number of columns and rows:
  pwmVal = 100;

  pinMode(SERVOPIN, OUTPUT); //OC2A output is D11

  //init message:
  lcd.print("I am a HERO!(BC)");
  lcd.setCursor(0, 1);
  lcd.print("Servo tester!");
  delay(2000);

  //clear LCD, set basics
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Servo Testing...");
}

void loop() {
  unsigned long currentMillis = millis();
  unsigned long timeDif = currentMillis - previousMillis;
  if (timeDif >= interval) {
    previousMillis = currentMillis; //reset counter
    unsigned int x;

    x = analogRead(A0); //read buttons
    if (x < 60) { //right button
      if (pwmVal < 231) {
        pwmVal += 10;
      }
    }
    else if (x < 200) { //up button
      if (pwmVal < 240) {
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
    else if (x < 800) { //select = reset button
      //Do nothing yet
    }

    lcd.setCursor(0, 1);
    lcd.print("ServoVAL: ");
    lcd.print(pwmVal);
    lcd.print("  "); //clear excess characters
  }
  digitalWrite(SERVOPIN, HIGH);
  delayMicroseconds(800); //5*180=900 microseconds
  delayMicroseconds(pwmVal*7); //5*180=900 microseconds
  digitalWrite(SERVOPIN, LOW);
  delayMicroseconds(1200-(pwmVal*7)); //fill up to one millisecond
  delay(18); //Complete 20ms period  
}
