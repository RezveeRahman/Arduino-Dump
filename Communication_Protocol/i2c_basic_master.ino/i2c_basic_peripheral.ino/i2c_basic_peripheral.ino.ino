/**
 * @author: Rezvee Rahman
 * @date:   06/25/2025
 *
 * @details: We are going to be prototyping some I2C.
 *           This sketch will be the peripheral board
 *           controller.
 *           
 *           The pins for I2C will be SCL and SDA pins.
 *           Our target will be a second arduino.
 */

#include <Wire.h>
#include <EEPROM.h>

#define ADDRESS      8 /* Address Group */
#define BAUD_RATE    9600
#define BUFFER_SIZE  32
#define CLK_FREQ     100000 /* 100KHz SCL - standard */
#define WIRE_TIMEOUT 2500

/* It writes 8 bits (1 byte), range 0 - 1023 (1kb)?*/
#define EEPROM_START_ADDR 0x0
#define EEPROM_HALF_ADDR  0x511
#define EEPROM_END_ADDR   0x1023

#define EEPROM_RANGE_BYTE   0x1 /* 1 byte in 1 byte */  
#define EEPROM_RANGE_H_WORD 0x2 /* 2 byte in 1 half-word */
#define EEPROM_RANGE_WORD   0x4 /* 4 byte in 1 word */


int handler_iter = 0;
byte eeprom_addr_ptr;
char wire_buffer[BUFFER_SIZE];

void requestEventHandler();

/**
 * In our setup loop we will do the following:
 * O - Add a event handler when the master sends
 *     us data to write to.
 * O - Setup the Baud rate of the peripheral
 *     device.
 */
void setup() {
    eeprom_addr_ptr = EEPROM_START_ADDR;
    Wire.setClock(CLK_FREQ);
    Wire.onReceive(requestEventHandler);
    Wire.setWireTimeout(WIRE_TIMEOUT);


    /* Serial for Output debugging. */
    Serial.begin(BAUD_RATE);
    Wire.begin(ADDRESS);
}

void loop() {
  // delay (500); /* Random half second delay lol. */
}

/**
 * This function is responsible to capture data bytes
 * from the master controller. We will write the
 * message to the EEPROM. 
 */
void requestEventHandler() {
    Serial.println("Got message processing.");
    for (handler_iter=0; handler_iter < BUFFER_SIZE; handler_iter++) {
      wire_buffer[handler_iter] = (char)Wire.read(); 
    }
    Serial.println("Processed message");
    Serial.println(wire_buffer);
}