/**
 * @author: Rezvee Rahman
 * @date: 08/24/2024
 *
 * @Description: Combining Arduino Analog stick with the
 * arduino LCD display. The display will show the X and Y axis
 * of the controller.
 */

/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld

*/

// include the library code:
#include <Arduino.h>
#include <LiquidCrystal.h>
#include <time.h>

#define RS_PIN_TO_ARDUINO       3
#define RW_PIN_TO_ARDUINO       4
#define ENABLE_PIN_TO_ARDUINO   5
#define D0_PIN_TO_ARUDINO       6
#define D1_PIN_TO_ARUDINO       7
#define D2_PIN_TO_ARUDINO       8
#define D3_PIN_TO_ARUDINO       9
#define D4_PIN_TO_ARUDINO       10
#define D5_PIN_TO_ARUDINO       11
#define D6_PIN_TO_ARUDINO       12
#define D7_PIN_TO_ARUDINO       13

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

/**
 * @param rs
 * @param enable
 * @param d4
 * @param d5
 * @param d6
 * @param d7
 */
LiquidCrystal lcd(RS_PIN_TO_ARDUINO,
                  ENABLE_PIN_TO_ARDUINO,
                  D0_PIN_TO_ARUDINO,
                  D1_PIN_TO_ARUDINO,
                  D2_PIN_TO_ARUDINO,
                  D3_PIN_TO_ARUDINO,
                  D4_PIN_TO_ARUDINO,
                  D5_PIN_TO_ARUDINO,
                  D6_PIN_TO_ARUDINO,
                  D7_PIN_TO_ARUDINO);

void setup() {
  time_t my_timer = time(NULL);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Time until detonation");
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis() / 1000);
}
