/**
 * @author: Rezvee Rahman
 * @date: 01/13/2025
 *
 * @description: Doing my first UART. We are sending
 * messages to the same arduino.
 */

#include <HardwareSerial.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TX D1
#define RX D0

#define BAUD_RATE 8

int incomingByte = 0;

void setup() {
  Serial.begin(BAUD_RATE);
  
}

void loop() {
  if (Serial.available() > 0) {
    while (Serial.available() > 0) {
      incomingByte = Serial.read();
      Serial.print("I Received: ");
      Serial.println(incomingByte, DEC);   
    }

  }
}
