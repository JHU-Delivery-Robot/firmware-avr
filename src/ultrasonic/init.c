/**
 * System initialization functions implementation
 */
#include "init.h"
#include "pinmap.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "stdint.h"
#include "bit_utils.h"

void AppInit() {
    
    //PORTB.DIR = 0x00; // Set all pins to input mode, including echoPin
    //PORTB.DIR = (1<<trigPin); 
	PORTB.DIRCLR = (1<<echoPin); // Set echo pin to 0 - Input
	PORTB.DIRSET = (1<<trigPin); // Set trigPin to output mode
	PORTB.PIN5CTRL |= PORT_ISC_RISING_gc;
    
}
