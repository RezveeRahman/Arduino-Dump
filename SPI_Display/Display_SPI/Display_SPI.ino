/**
 * @author: Rezvee Rahman
 * @date:   06/3/2025
 *
 * @details: This program interfaces with another arduino.
 *           The code is for a <b>Master</b> board. It
 *           interacts with a Slave output.
 *          
 *            This board is a R4 Minima Arduino Official.
 */

#define LCD_SR 3 /* Select Register     */
#define LCD_RW 4 /* Read and Write mode */

#define LCD_ENABLE 5

#define LCD_D_OUT 8

#define LCD_D0  6
#define LCD_D1  7
#define LCD_D2  8
#define LCD_D3  9
#define LCD_D4 10
#define LCD_D5 11
#define LCD_D6 12
#define LCD_D7 13

/* Define Constants (Stupid aliasing bs) */
const uint8_t D_OUT[] = 
  { LCD_D0, LCD_D1, LCD_D2, LCD_D3,
    LCD_D4, LCD_D5, LCD_D6, LCD_D7 }; 

/**
 * 
 */
void setup() {
  int i;

  pinMode(LCD_SR, OUTPUT);
  pinMode(LCD_RW, OUTPUT);
  pinMode(LCD_ENABLE, OUTPUT);
  for (i = 0; i < LCD_D_OUT; i++) {
    pinMode(D_OUT[i], OUTPUT);
  }

  
}

/**
 *
 */
void loop() {

}