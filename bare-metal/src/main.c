/**
 * @author: Rezvee Rahman
 * @date:   07/20/2025
 *
 * @details: Bare metal programming on an arduino.
 *           credit to: Low Level YT
 *           https://www.youtube.com/watch?v=j4xw8QomkXs
 */

#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    DDRB = DDRB | (1 << DDB5);

    while (1) {
        PORTB = PORTB | (1 << PORTB5);
        _delay_ms(1000);
        PORTB = PORTB & ~(1 << PORTB5);
        _delay_ms(1000);
    }

    return (0);
}
