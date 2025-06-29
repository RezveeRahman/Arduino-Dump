/**
 * @author: Rezvee Rahman
 * @date: 11/28/2024
 *
 * @description: Doing some basic christmas lights.
 */

/* Includes */
#include <Arduino.h>
#include <math.h>

/* Define PINS being used. Digital pins to Arduino */
#define D2_PIN_TO_ARDUINO 2
#define D4_PIN_TO_ARDUINO 4
#define D7_PIN_TO_ARDUINO 7
#define USED_PINS         3

/* Define Pattern Number Assignments */
#define SEQUENTIAL 0
#define RAPID      1
#define RANDOM     2

/* Functions for blinking lights */
static void turnOffPins(void);

/* Blinking pattern functions */
// static int  pickBlinkPattern(void);
static void sequentialBlink (void);
static void rapidFlashBlink (void);
// static void randFlashBlink  (void);

static int const PIN_LIST[USED_PINS] =
    {D2_PIN_TO_ARDUINO,
     D4_PIN_TO_ARDUINO,
     D7_PIN_TO_ARDUINO};


/*
 * Local Variables
 */

/* Delay Befor the pin gets output value */
static unsigned short const LOW_BOUND_RANDOM_NUM   = 1;
static unsigned short const HIGH_BOUND_RANDOM_NUM  = 2;
static long Delay;

/* Random pattern uses these constants to determine which one to pick */
static unsigned short const FIRST_PIN = 0;
static unsigned short const LAST_PIN  = USED_PINS - 1;


/**
 * This setups the arduino before going into the execution
 * loop.
 */
void setup() {
    /* Setup the Pins as output pins */
    pinMode(D2_PIN_TO_ARDUINO, OUTPUT);
    pinMode(D4_PIN_TO_ARDUINO, OUTPUT);
    pinMode(D7_PIN_TO_ARDUINO, OUTPUT);
}

/**
 * This goes into the execution loop.
 */
void loop() {
    turnOffPins();
    sequentialBlink();
    rapidFlashBlink();
    randFlashBlink();
}

static void turnOffPins() {
  digitalWrite(D2_PIN_TO_ARDUINO, LOW);
  digitalWrite(D4_PIN_TO_ARDUINO, LOW);  
  digitalWrite(D7_PIN_TO_ARDUINO, LOW);
}

/* Functions for blinking lights */
static void sequentialBlink(void) {
    long delay_num;
    int  i;

    delay_num = random(LOW_BOUND_RANDOM_NUM,
        HIGH_BOUND_RANDOM_NUM); 

    for (i = 0; i < USED_PINS; i++) {
        delay(delay_num * 1000);
        digitalWrite(PIN_LIST[i], HIGH);
    }
    delay (1000);
}

static void rapidFlashBlink(void) {
  int i;
  int j;

  for (i = 0; i < 8; i++) {
    turnOffPins();
    delay (250);
    for (j = 0; j < USED_PINS; j++) {
      digitalWrite(PIN_LIST[j], HIGH);
    }
    delay (250);
  }
  delay(1000);
}

static void randFlashBlink(void) {
  int i;
  int pin;

  for (i = 0; i < 45; i++) {
    /* WTF??? This random function is stupid! */
    pin = random(FIRST_PIN, LAST_PIN + 1);
    delay (100);
    digitalWrite(PIN_LIST[pin], HIGH);
    delay (100);
    turnOffPins();
  }
}