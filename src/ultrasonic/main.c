/**
 * main (entrypoint) implementation
 */
#include "init.h"
#include "pinmap.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "stdint.h"
#include "bit_utils.h"
#include "globals.h"

// volatile long Counter;
volatile unsigned duration;
volatile long cm, inches; // Make Note
// void delay (long n) {          // Delay by n milliseconds
// 	Counter = 469 * n;
// 	do Counter--; while (Counter != 0);
// }


ISR(PORTB_PORT_vect)
{
	if(PB5_INTERRUPT)
	{
		pb5Ioc = 1;
		PB5_CLEAR_INTERRUPT_FLAG;
	}
}




void loop(void) {
    PORTB.OUT &= ~(1<<trigPin); // Ensure clean HIGH pulse by providing short LOW pulse first
    _delay_us(5);
    PORTB.OUT |= (1<<trigPin); // Trigger Pin HIGH for 10 ms (Minimum for HC-SR04)
     _delay_us(10);
    PORTB.OUT &= ~(1<<trigPin); // Trigger Pin LOW
	
	// Start Timer in Micro Seconds, Wait until pb5Ioc goes High, then stop
	unsigned duration = 0;
	while (!pb5Ioc)
	{ 
		_delay_us(1);
	}
	
	// When pb5Ioc Goes High
	// Convert the time into a distance
	cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
	inches = (duration/2) / 74;   // Divide by 74 or multiply by 0.0135
	
	duration = 0;
	pb5Ioc = 0;


}

int main(void) {
    AppInit();
    for(;;) loop();
}
