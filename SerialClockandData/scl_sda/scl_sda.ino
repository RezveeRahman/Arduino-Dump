/**
 * @author: Rezvee Rahman
 * @date: 01/06/2025
 * 
 * @details: We are doing some basic testing of the Arduino Clock and
 * I2C communciations.
 */

#include <Arduino.h>
#include <Wire.h>
#include <unistd.h>

/**
 * Speed Hz:
 *       0
 *   10000
 *  100000
 *  400000
 * 1000000
 * 3400000
 */
const static uint32_t CLK_SPD = 1;
const static byte x = 0;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Wire.setClock(CLK_SPD);

}

void loop() {
  // put your main code here, to run repeatedly:
  Wire.beginTransmission(4);
  Wire.write("x is ");
  Wire.write(x);
  Wire.endTransmission();
}
