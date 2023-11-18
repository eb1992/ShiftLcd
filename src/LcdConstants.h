#ifndef LcdConstants_h
#define LcdConstants_h

// Constants here are derived from the data sheet for the HD44780U

// Namespace containing constants related to LCD operations
namespace LCD {
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
}

#endif