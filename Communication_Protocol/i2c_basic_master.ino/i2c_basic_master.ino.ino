/**
 * @author: Rezvee Rahman
 * @date:   06/25/2025
 *
 * @details: We are going to be prototyping some I2C.
 *           This sketch will be the master board
 *           controller.
 *           
 *           The pins for I2C will be SCL and SDA pins.
 *           Our target will be a second arduino.
 */

#include <Wire.h>

#define BAUD_RATE        9600
#define CLK_FREQ         100000 /* 100KHz SCL - standard */
#define DATA_MAX_DECIMAL 90
#define DATA_MIN_DECIMAL 65
#define TARGET_ADDRESS   8
#define WIRE_TIMEOUT     2500 /* Timeout is 2.5 seconds */

const char my_message[32] = "Hello my friend, how are you? \0";
byte randomNumber;

void setup() {
  Serial.println("Starting!");
  Wire.setTimeout(WIRE_TIMEOUT);

  Wire.setClock(CLK_FREQ);
  Wire.begin();
}

void loop() {
  Wire.beginTransmission(TARGET_ADDRESS);
  Wire.write(my_message);
  Wire.endTransmission();
}
