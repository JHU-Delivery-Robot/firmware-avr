/**
 * System initialization functions implementation
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "init.h"
#include "pinmap.h"
#include "stdint.h"
#include "bit_utils.h"
#include "timercontrol.h"

void AppInit() {

	/* prep and start timer */
	TCA0_init();
    
    //PORTB.DIR = 0x00; // Set all pins to input mode, including echoPin
    //PORTB.DIR = (1<<trigPin); 
	
	PORTA.DIRCLR = (1<<echoPinA); // Set echo pin to 0 - Input
	PORTA.DIRSET = (1<<trigPinA); // Set trigPin to output mode
	PORTA_PIN2CTRL |= PORT_ISC_RISING_gc;


	PORTA.DIRCLR = (1<<echoPinB); // Set echo pin to 0 - Input
	PORTA.DIRSET = (1<<trigPinB); // Set trigPin to output mode
	PORTA.PIN4CTRL |= PORT_ISC_RISING_gc;
}
