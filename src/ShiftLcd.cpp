#include "Arduino.h"
#include "ShiftLcd.h"


//-- Public functions ------------------------------------------------------\\

// Constructor: Initializes the ShiftLcd object with pin numbers
ShiftLcd::ShiftLcd(int LCD_EN, int LCD_D7, int SHIFT_SER, int SHIFT_SRCLK):
  EN(LCD_EN),
  D7(LCD_D7),
  SER(SHIFT_SER),
  CLK(SHIFT_SRCLK){
}

// Begin function to initiate the display
// Should be called from setup()
void ShiftLcd::begin(){
  // Initialize pin modes and set initial state
  digitalWrite(EN, LOW);
  pinMode(EN, OUTPUT);
  pinMode(D7, INPUT);
  pinMode(SER, OUTPUT);
  digitalWrite(CLK, LOW);
  pinMode(CLK, OUTPUT);

  // Set initial conditions and configuration for the LCD
  updateTime();
  checkBusyFlag();
  writeDisplay(FUNCTION_SET_8, WRITE_INSTR); // Set display to 8-pin mode
  shiftData(FUNCTION_SET_INIT_4, WRITE_INSTR); // Set display to 4-pin mode
  togglePin(EN);
  checkBusyFlag();
  writeDisplay(FUNCTION_SET_4, WRITE_INSTR);
  on();
  writeDisplay(ENTRY_MODE_SET, WRITE_INSTR);
  clear();
}

// Overloaded function for writing to display, 
// calls the private writeString function
void ShiftLcd::write(char msg[]){
  writeString(msg);
}

void ShiftLcd::write(char msg1[], char msg2[]){
  writeString(msg1);
  writeDisplay(LINE_TWO, WRITE_INSTR);
  writeString(msg2);
}

void ShiftLcd::write(char msg[], int n){
  writeString(msg, intToString(n));
}

void ShiftLcd::write(String msg){
  writeString(msg.c_str());
}

void ShiftLcd::write(String msg1, String msg2){
  writeString(msg1.c_str(), msg2.c_str());
}

void ShiftLcd::write(String msg, int n){
  writeString(msg.c_str(), intToString(n));
}

void ShiftLcd::write(int n){
  writeString(intToString(n));
}

// Shift the display text one step to the left
void ShiftLcd::shiftLeft(){
  writeDisplay(LEFT_SHIFT, WRITE_INSTR);
}

// Shift the display text one step to the right 
void ShiftLcd::shiftRight(){
  writeDisplay(RIGHT_SHIFT, WRITE_INSTR);
}

// Scrolls the display to the right with the provided delays speed
// Should be called (repeatedly) from loop()
void ShiftLcd::scrollRight(unsigned long delay){
  timedFunc(delay, &ShiftLcd::shiftRight);
}

// Scrolls the display to the left with the provided delays speed
// Should be called (repeatedly) from loop()
void ShiftLcd::scrollLeft(unsigned long delay){
  timedFunc(delay, &ShiftLcd::shiftLeft);
}

// Blinks the display with the provided delays speed
// Should be called (repeatedly) from loop()
void ShiftLcd::blink(unsigned long delay){
  timedFunc(delay, &ShiftLcd::onOff);
}

// Turn the displayed text on
void ShiftLcd::on(){
  writeDisplay(DISPLAY_ON, WRITE_INSTR); 
  isOn = true;
}

// Turn the displayed text off 
void ShiftLcd::off(){
  writeDisplay(DISPLAY_OFF, WRITE_INSTR); 
  isOn = false; 
}

// Clears the text from the display
void ShiftLcd::clear(){
  writeDisplay(CLEAR_DISPLAY, WRITE_INSTR);
  for(uint8_t i = 0; i < N_BUSY_FLAG_TICKS; i++){
    checkBusyFlag();
  }
}


//-- Private functions -----------------------------------------------------\\

// Write a character at a time to the display
void ShiftLcd::writeString(const char* msg){
  for(uint8_t i = 0; i < strlen(msg); i++){
    writeDisplay(msg[i], WRITE_CHAR);
  }
  writeDisplay(LINE_ONE, WRITE_INSTR);
}

void ShiftLcd::writeString(const char* msg1, const char* msg2){
  writeString(msg1);
  writeDisplay(LINE_TWO, WRITE_INSTR);
  writeString(msg2);
}

// Calls the provided function if the provided delay has passed since the 
// last time the function was called. Using a non-blocking delay.
void ShiftLcd::timedFunc(unsigned long delay, void (ShiftLcd::*func)()){
  if(timePassed(delay)){
    (this->*func)();
    updateTime();
  }
}

// Turns the display on if its off, otherwise turns it off
void ShiftLcd::onOff(){
  isOn ? off() : on();
}

// Toggles the provided pin off/on/off
void ShiftLcd::togglePin(uint8_t pin){
  digitalWrite(pin, LOW);
  digitalWrite(pin, HIGH);
  digitalWrite(pin, LOW);
}

// Checks if the display is ready for a new instruction
void ShiftLcd::checkBusyFlag(){
  shiftData(READ_BUSY_FLAG, READ_INSTR);
  do{
    togglePin(EN);
  } 
  while(digitalRead(D7)); 
}

// Shifts out the data and the control signals 
// one bit at the time to the serial pin
void ShiftLcd::shiftData(uint8_t data, uint8_t controlSignals){
  const int LSB_MASK = 0x0001;
  const int N_CONTROL_BITS = 2;
  const int N_DATA_BITS = 4;

  for(int i = 0; i < N_CONTROL_BITS; i++){
    digitalWrite(SER, (controlSignals >> i) & LSB_MASK);
    togglePin(CLK);
  }
  for(int i = 0; i < N_DATA_BITS; i++){
    digitalWrite(SER, (data >> i) & LSB_MASK);
    togglePin(CLK);
  }
  togglePin(CLK);
}

// Write the provided data to the display 
// Splits the data argument byte in two and calls the shiftData 
// function with the MSBs and LSBs
void ShiftLcd::writeDisplay(uint8_t data, uint8_t controlSignals){
  const int SHIFT_AMOUNT = 4;

  for(int i = SHIFT_AMOUNT; i >= 0; i -= SHIFT_AMOUNT){
    shiftData(data >> i, controlSignals);
    togglePin(EN);
    checkBusyFlag();
  }
}

// Puts the units / tens / hundreds etc in the number buffer
// Returns a pointer to the first place in the buffer that is a non zero
const char* ShiftLcd::intToString(int n){
  const uint8_t RADIX = 10;
  const uint8_t ASCII_ZERO = '0';
  const uint8_t UNIT_DIGIT_INDEX = strlen(numBuffer) - 1;

  for(uint8_t i = UNIT_DIGIT_INDEX; i >= 0; i--){
    numBuffer[i] = (n % RADIX) + ASCII_ZERO;
    n = n / RADIX;
    if(n == 0){
      return numBuffer + i;
    }
  }
  return numBuffer;
}

// Update the time variable used by timed function
void ShiftLcd::updateTime(){
  prevTime = millis();
}

// Returns if the delay time has passed
bool ShiftLcd::timePassed(unsigned long delay){
  return millis() - prevTime >= delay;
}
