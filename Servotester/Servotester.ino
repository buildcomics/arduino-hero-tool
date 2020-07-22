/*
  LiquidCrystal Library
  modified from liquid Crystal example.

  https://www.arduino.cc/en/Tutorial/LiquidCrystal

  Servo timer 2 library from https://github.com/nabontra/ServoTimer2
  Guide by https://www.hackster.io/ashraf_minhaj/how-to-use-servotimer2-library-simple-explain-servo-sweep-512fd9

  Modified for Servo by https://www.buildcomics.com
  
  Wiring & Latest code: https://github.com/buildcomics/arduino-hero-toolbox
*/
//Define our servopin number here (2 is used here, it allows to connect the servo connector directly to the bottom left of the 2x5 pin default header, see https://github.com/buildcomics/arduino-hero-toolbox
#define SERVOPIN 2

#include <LiquidCrystal.h> // include the library code for the display
#include <ServoTimer2.h>  // the servo library


LiquidCrystal lcd(8, 9, 4, 5, 6, 7);           // select the pins used on the LCD panel
unsigned long int previousMillis; //Holds previous millis for updating time
const unsigned int interval = 100; //This is our interval for updating the screen
unsigned int pwmVal; //This value holds our set pwm value
ServoTimer2 servo; //The servo object

void setup() {
  lcd.begin(16, 2);   // set up the LCD's number of columns and rows:
  pwmVal = 90; //Initializing the pwm value to 90 degrees

  servo.attach(SERVOPIN); //Attach servo timer 2 object to SERVOPIN
    
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
      if (pwmVal <= 170) {
        pwmVal += 10;
      }
    }
    else if (x < 200) { //up button
      if (pwmVal < 180) {
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
  servo.write(map(pwmVal, 0, 180, 750, 2250)); //Map values 0 to 180 to pwm timer 1 values and write
}
