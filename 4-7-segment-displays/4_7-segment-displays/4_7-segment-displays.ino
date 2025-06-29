/**
 * @author: Rezvee Rahman
 * @date:   05/4/2025
 *
 * @details: This is code for a 4 - 7 segment display.
 *           We use a CD4511BE chip to translate the
 *           hexadecimal values to the appropriate pins.
 */

/**
 * Map:
 *
 * CD4511BE is the Binary to Hex encoder (converter?).
 * Digital Pins (10 - 13) - CD4511BE 
 * 10 - D0 
 * 11 - D1
 * 12 - D2
 * 13 - D3
 *
 * 5641AS is the 4 - 7 segment display. Here we have the
 * the following pins.
 *
 * 1 - AS_D1
 * 2 - AS_D2
 * 3 - AS_D3
 * 4 - AS_D4
 *
 * 5 - AS_DP (Dot)
 */

#define CD4511BE_D0 10
#define CD4511BE_D1 11
#define CD4511BE_D2 12
#define CD4511BE_D3 13

#define DISPLAY_5641_AS_1 1
#define DISPLAY_5641_AS_2 2
#define DISPLAY_5641_AS_3 3
#define DISPLAY_5641_AS_4 4

#define DISPLAY_5651_AS_DP 5

#define PINS_USED 9 /* We are using 9 pins. All outputs. */


/**
 * Global variables
 */
static int const PIN_LIST[] = {
    CD4511BE_D0, CD4511BE_D1, CD4511BE_D2, CD4511BE_D3,
    DISPLAY_5641_AS_1, DISPLAY_5641_AS_2, DISPLAY_5641_AS_3, DISPLAY_5641_AS_4,
    DISPLAY_5651_AS_DP
};

static int i;

void setup() {
    for (i = 0; i < PINS_USED; i++) {
        pinMode(PIN_LIST[i], HIGH);
    }
}

void loop() {
  // put your main code here, to run repeatedly:

}
