#include "ShiftLcd.h"

// Pin configuration for LCD and photoresistor
const int LCD_EN = 2;
const int LCD_D7 = 3;
const int SHIFT_SER = 4;
const int SHIFT_SRCLK = 5;
const int photoPin = A5;

// LCD instance with specified pin numbers
ShiftLcd lcd(LCD_EN, LCD_D7, SHIFT_SER, SHIFT_SRCLK);

void setup() {
  // Set photoresistor pin as INPUT
  pinMode(photoPin, INPUT);
  
  // Initialize the LCD display
  lcd.begin();
}

void loop() {
  // Create a string to display light level information
  String lightLevelString = "Light level is: ";

  // Read analog value from photoresistor
  int photoresistorValue = analogRead(photoPin);

  // Define mapping parameters
  int analogMin = 0;
  int analogMax = 1023;
  int outputMin = 0;
  int outputMax = 100;

  // Map the photoresistor value to a percentage
  int currentLightLevel = map(photoresistorValue, analogMin, analogMax, outputMin, outputMax);

  // Concatenate light level value to the string
  lightLevelString += currentLightLevel;
  lightLevelString += "%";

  // Display light level information on the LCD
  lcd.write(lightLevelString);

  // Define loop count
  int nShifts = 10;
  int delayTime = 700;

  // Shift the text on the LCD to the left for a specific number of times with a delay
  for (int i = 0; i < nShifts; i++) {
    delay(delayTime);
    lcd.shiftLeft();
  }

  // Clear the LCD display
  lcd.clear();
}
