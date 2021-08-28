/* Arduino Uno Blink sketch for use with the empty core */
#define F_CPU 3333333
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "stdint.h"
#include "bit_utils.h"

const int led = 5; // In port B
const int intr = 6;
const int int_led = 7;


ISR(PORTB_PORT_vect, ISR_BLOCK) {
    if(PORTB.INTFLAGS & (1<<intr)) {
        PORTB.OUTTGL = 1<<int_led;
    }
}

void setup() {
    PORTB.PIN6CTRL = PORT_ISC_RISING_gc // enable interrupt on rising edge
                     | _VAL2FLD(PORT_PULLUPEN, 0)
                     | _VAL2FLD(PORT_INVEN, 0);
    PORTB.DIR = PORTB.DIR | 1<<led;         // Define PB5 as an output
    sei();
}

volatile long Counter;

void delay (long n) {          // Delay by n milliseconds
    Counter = 469 * n;
    do Counter--; while (Counter != 0);
}

// The loop routine runs over and over again forever:
void loop() {
    PORTB.OUT = PORTB.OUT | 1<<led;      // Take PB5 high
    _delay_ms(500);              // Wait for a second
    PORTB.OUT = PORTB.OUT & ~(1<<led);   // Take PB5 low
    _delay_ms(500);                 // Wait for a second
}

// We need main()
int main() {
    setup();
    for(;;) loop();
}
