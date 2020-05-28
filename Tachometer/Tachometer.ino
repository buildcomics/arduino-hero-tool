/*
  LiquidCrystal Library
  modified from liquid Crystal example.

  http://www.arduino.cc/en/Tutorial/LiquidCrystal

  Modified for Tacho by https://www.buildcomics.com
*/

#include <LiquidCrystal.h> // include the library code:

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);           // select the pins used on the LCD panel
const byte interruptPin = 2; //the pin connected to the sensor
unsigned long int turnCount, turnStart, turnEnd; // variables to store turncount and timings for RPM
unsigned long previousMillis = 0;        // timing variable
const long interval = 100;           // interval at which to measure
unsigned int divFactor; //variable for easy division

void setup() {
  lcd.begin(16, 2);   // set up the LCD's number of columns and rows:
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), count, FALLING); //Call count function on falling edge
  turnCount = 0;
  turnStart = 0;
  divFactor = 1;
  turnEnd = millis();

  //init message:
  lcd.print("I am a HERO!(BC)");
  lcd.setCursor(0, 1);
  lcd.print("Tachometer!");
  delay(2000);

  //clear LCD, set basics
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("RPM:      DIV:1");
  lcd.setCursor(0, 1);
  lcd.print("Turns:");
}

void loop() {
  unsigned long currentMillis = millis();
  unsigned long timeDif = currentMillis - previousMillis;

  if (timeDif >= interval) {
    unsigned int x;
    x = analogRead (0); //read buttons
    if (x < 60) { //right button
      //lcd.print ("Right");
    }
    else if (x < 200) { //up button
      if (divFactor < 10) {
        divFactor++;
      }
    }
    else if (x < 400) { //down button
      if (divFactor > 1) {
        divFactor--;
      }
    }
    else if (x < 600) { //left button
      //lcd.print ("Left  ");
    }
    else if (x < 800) { //select = reset button, reset turnCount;
      turnCount = 0;
    }
    previousMillis = currentMillis; //reset counter

    //print turns
    lcd.setCursor(6, 1);
    lcd.print(turnCount / divFactor);
    lcd.print("               "); //clear line

    //calculate rpm
    unsigned long int timeSinceTurn = currentMillis - turnEnd;
    unsigned long int turnLength = turnEnd - turnStart;
    if ( turnLength < timeSinceTurn) { //if it was longer than the last rotation since we got an update, use the current time for rpm calculation
      turnLength = timeSinceTurn;
    }
    unsigned long int rpm = 1000 / turnLength * 60;
    //print RPM
    lcd.setCursor(4, 0);
    lcd.print("               "); //clear line
    lcd.setCursor(4, 0);
    lcd.print(rpm / divFactor);

    //print Division factor
    lcd.setCursor(11, 0);
    lcd.print("DIV:");
    lcd.print(divFactor);
  }
}
void count() {
  turnCount++;
  turnStart = turnEnd;
  turnEnd = millis();
}
