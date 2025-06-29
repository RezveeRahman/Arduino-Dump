/**
 * @author: Rezvee Rahan
 * @date: 01/17/2025
 *
 * @details: Just some code for the 7474 D-Flip Flop IC
 */

/**
 * INCLUDES
 */
#include <Arduino.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Function Defs
 */
void static _cycle_clock(void);

/**
 * MACROS:
 * 
 * Anything labeled with Output will be outgoing from Arduino
 * Anything labeled with Input will be inbound to Arduino
 */
#define CLK_TIME_DELAY 250 /* Delay for our CLK*/

#define CLK  13 /* Output */
#define D    11 /* Output */
#define CLR  12 /* Output */

/* What Q is*/
#define LED 13


static int _send_bit;

/**
 * Initial Setup here.
 */
void setup() {
  pinMode(CLK, OUTPUT);
  pinMode(D,   OUTPUT);
  pinMode(CLR, OUTPUT);
  pinMode(LED, OUTPUT);

  pinMode (1, OUTPUT);

  _send_bit = 0;
}

/* Super loop */
void loop() {
  /* switch between turning the D pin off and on */
  if (_send_bit == 0) {
    digitalWrite(D, HIGH);
    _send_bit = 1;
  } else {
    digitalWrite(D, LOW);
    _send_bit = 0;
  }

  _cycle_clock();
}

void static _cycle_clock(void) {
  digitalWrite(CLK, HIGH);
  digitalWrite(D, HIGH);
  delay (CLK_TIME_DELAY);
  digitalWrite(CLK, LOW);
  digitalWrite(D, LOW);
  delay (CLK_TIME_DELAY);
}
