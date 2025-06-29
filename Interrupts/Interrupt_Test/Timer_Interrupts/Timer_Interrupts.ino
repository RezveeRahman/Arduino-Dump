/**
 * @author: Rezvee Rahman
 * @date: 02/06/2025
 *
 * @details: Arduino Interrupts, But I'm using the timer interrupts.
 *           This one, while sounds complicated, is pretty basic.
 *
 * Links to where I got some of the information from.
 * @information: https://deepbluembedded.com/arduino-timer-interrupts/
 */

/* INCLUDES */

/* DEFINES */
#define SERIAL_RATE     9600
#define TIMER_PRELOAD   40535
#define PRESCALAR       B00000011

/** PINS **/

/**
 * Timer0
 * O - 8 Bit resolution
 * 1 - Mostly used for delay(), millis(), macros()
 * 2 - 
 */
#define T0 9

/* Interrupt Service Routine */
ISR (TIMER1_OVF_vect) {
  /* Initialize */
  TCCR1A  = 0;
  TCCR1B  = 0;


  TCCR1B |= PRESCALAR;
  TCNT1   = TIMER_PRELOAD;
  
}

void setup() {

}

void loop() {

}
