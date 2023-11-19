#ifndef ShiftLcd_h
#define ShiftLcd_h

#include "Arduino.h"

// Define constants for default blink and scroll times
#define BLINK_TIME 800
#define SCROLL_TIME 400

// Class definition for ShiftLcd
class ShiftLcd {
public:
  // Constructor: Initializes the LCD with specified pin numbers
  ShiftLcd(int LCD_EN, int LCD_D7, int SHIFT_SER, int SHIFT_SRCLK);

  // Public methods for basic LCD control
  void begin();  // Initialize the LCD
  void on();     // Turn on the LCD
  void off();    // Turn off the LCD
  void shiftLeft();   // Shift the display text one step to the left
  void shiftRight();  // Shift the display text one step to the right
  void scrollRight(unsigned long delay = SCROLL_TIME);  // Scroll text to the right
  void scrollLeft(unsigned long delay = SCROLL_TIME);   // Scroll text to the left
  void blink(unsigned long delay = BLINK_TIME);         // Blink the display
  void clear();  // Clear the LCD display

  // Public methods for writing to the LCD
  void write(char msg[]);                     // Write a character array
  void write(char msg1[], char msg2[]);       // Write two character arrays
  void write(char msg[], int n);              // Write a character array and an integer
  void write(int n);                          // Write an integer
  void write(String msg);                     // Write a String
  void write(String msg1, String msg2);       // Write two Strings
  void write(String msg, int n);              // Write a String and an integer

private:
  // Private member variables for pin numbers and timing
  const uint8_t EN;
  const uint8_t D7;
  const uint8_t SER;
  const uint8_t CLK;

  // Private member constants for the LCD
  // See the documentation for the HD44780U:
  // https://www.sparkfun.com/datasheets/LCD/HD44780.pdf

  // Write instruction control byte
  const uint8_t WRITE_INSTR         = 0b00000000;

  // Read instruction control byte
  const uint8_t READ_INSTR          = 0b00000010;

  // Write character control byte
  const uint8_t WRITE_CHAR          = 0b00000001;

  // Function set initialization for 4-pin mode
  const uint8_t FUNCTION_SET_INIT_4 = 0b00000010;

  // Function set for 4-pin mode
  const uint8_t FUNCTION_SET_4      = 0b00101000;

  // Function set for 8-pin mode
  const uint8_t FUNCTION_SET_8      = 0b00111000;

  // Entry mode set control byte
  const uint8_t ENTRY_MODE_SET      = 0b00000110;

  // Cursor move to the beginning of the second line control byte
  const uint8_t LINE_TWO            = 0b11000000;

  // Cursor move to the beginning of the first line control byte
  const uint8_t LINE_ONE            = 0b10000000;

  // Display on control byte
  const uint8_t DISPLAY_ON          = 0b00001100;

  // Read busy flag control byte
  const uint8_t READ_BUSY_FLAG      = 0b11110111;

  // Clear display control byte
  const uint8_t CLEAR_DISPLAY       = 0b00000001;

  // Display off control byte
  const uint8_t DISPLAY_OFF         = 0b00001000;

  // Shift display to the right control byte
  const uint8_t RIGHT_SHIFT         = 0b00011100;

  // Shift display to the left control byte
  const uint8_t LEFT_SHIFT          = 0b00011000;

  // Number of busy flag ticks for checking readiness
  const uint8_t N_BUSY_FLAG_TICKS   = 8;


  // Private member variables for timing and state
  unsigned long prevTime;
  bool isOn;

  // Private member variable for converting integers to strings
  char* const numBuffer = "00000";

  // Private helper methods for internal LCD control
  void writeString(const char* msg);
  void writeString(const char* msg1, const char* msg2);
  void writeDisplay(uint8_t data, uint8_t controlSignals);
  void togglePin(uint8_t pin);
  void checkBusyFlag();
  void shiftData(uint8_t data, uint8_t controlSignals);
  const char* intToString(int n);
  void onOff();
  void timedFunc(unsigned long delay, void (ShiftLcd::*func)());
  bool timePassed(unsigned long delay);
  void updateTime();

  
};

#endif