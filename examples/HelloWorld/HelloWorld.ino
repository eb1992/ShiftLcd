#include "ShiftLcd.h"

// Pin configuration for LCD and Shift register
const int LCD_EN = 2;
const int LCD_D7 = 3;
const int SHIFT_SER = 4;
const int SHIFT_SRCLK = 5;

// LCD instance with specified pin numbers
ShiftLcd lcd(LCD_EN, LCD_D7, SHIFT_SER, SHIFT_SRCLK);

void setup() {
  // Initialize the LCD display
  lcd.begin();

  // Write text to the display
  lcd.write("Hello world!");
}

void loop() {
  // Scroll the text left with the default speed
  lcd.scrollLeft();
}
