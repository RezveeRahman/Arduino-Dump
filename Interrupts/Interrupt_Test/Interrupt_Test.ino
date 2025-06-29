/**
 * @author: Rezvee Rahman
 * @date: 02/03/2025
 *
 * @details: Doing some arduino interrupt testing.
 */

/* Function Headers */
void handleInterrupt(void);


/* DEFINES */
#define SERIAL_RATE 9600
#define BLINK_DELAY 1500

#define INIT_MSG "+------------------------------------------------------------+\n| O - This Micro-Controller was programmed by: Rezvee Rahman |\n| O - Copyrights-Free-and-Open-to-Use: Circa. 2025           |\n+------------------------------------------------------------+\n"""
#define INTERRUPT_MSG "+----------------------------+\n|  WE HAVE BEEN INTERRUPTED  |\n+----------------------------+\n"
#define RESUME_MSG "\n+-- Resuming Normal Operations --+\n"

/* Using ATMega328 Board we can do the following */
#define INTERRUPT_PIN 2
#define D3 3

bool active = true;

void setup() {
  /* Do not interrupt any set up code */
  Serial.begin(SERIAL_RATE);
  Serial.println("Initializing Arduino");
  Serial.println(INIT_MSG);
  
  pinMode(D3, OUTPUT);

  /* Interrupt PIN */
  pinMode(INTERRUPT_PIN, INPUT_PULLUP);
  /*
   * O LOW     - Trigger the Interrupt whenever the pin is low
   * O CHANGE  - to Trigger the Interrupt whenever the pin changes value
   * O RISING  - to Trigger when the pin goes from low to HIGH
   * O FALLING - for when the pin goes from high to low
   *
   * For Due, Zero, and MKR1000 boards:
   * O High to trigger the interrupt whenever the pins is high.
   */ 
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), handleInterrupt, FALLING);
}

void loop() {
  /* Re-enable interrupt */
  if (active) {
    digitalWrite(D3, HIGH);
    delay (BLINK_DELAY);
  }
  digitalWrite(D3, LOW);
  delay (BLINK_DELAY);  
}

void handleInterrupt() {
  Serial.println(INTERRUPT_MSG);
  if (active) {
    active = false;
  } else {
    active = true;
  }
  digitalWrite(D3, LOW);
}