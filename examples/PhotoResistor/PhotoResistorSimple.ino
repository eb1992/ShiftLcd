#include <ShiftLcd.h>

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
  // Read analog value from photoresistor
  int photoresistorValue = analogRead(photoPin);

  // Define mapping parameters
  int analogMin = 0;
  int analogMax = 1023;
  int outputMin = 0;
  int outputMax = 100;

  // Map the photoresistor value to a percentage
  int currentLightLevel = map(photoresistorValue, analogMin, analogMax, outputMin, outputMax);

  // Display light level information on the LCD
  lcd.write(currentLightLevel);

  // Clear the LCD display
  lcd.blink();
}
