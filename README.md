# ShiftLcd Library for Arduino

This Arduino library provides an easy-to-use interface for controlling an HD44780U (or similar) LCD display with a SN74HC595 (or similar) shift register. It can control the display with only four pins from the Arduino. 

## Table of Contents

- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)

## Features

- Display text on an LCD screen.
- Scroll text left or right with customizable delays.
- Blink the display with a specified blink rate.
- Clear the display for a clean slate.

## Installation
1. Connect everything according to the picture:
  * The pull down resistor connected to the LCDs D7-pin should be ca 10 kOhms.
  * The 10 kOhms potentiometer connected to the LCDs V0-pin can be replaced by a ca 5 kOhms resistor.

![Connections](extras/Connections.png)

2. In the Arduino IDE: Sketch > Include Library > Manage Libraries.

3. Select ShiftLcd.

## Usage

1. Include the `ShiftLcd` library in your Arduino sketch and create an instance of it:

```cpp
  #include "ShiftLcd.h"

  int LCD_EN = 2;
  int LCD_D7 = 3; 
  int SHIFT_SER = 4; 
  int SHIFT_SRCLK = 5;

  ShiftLcd lcd(LCD_EN, LCD_D7, SHIFT_SER, SHIFT_SRCLK);
```
2. Initialize the LCD in the setup() function and write a message:

```cpp
  void setup() {
    lcd.begin();
    lcd.write("Hello, World!");
  }
```
3. Use the library functions to control the LCD in the loop() function:

```cpp
  void loop() {
    lcd.scrollLeft();
  }
```
