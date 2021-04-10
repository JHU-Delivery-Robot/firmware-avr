/**
 * main (entrypoint) implementation
 */
#include "timercontrol.h"
#include "init.h"
#include "pinmap.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "stdint.h"
#include "bit_utils.h"
#include "globals.h"


float getDistanceA() {
	PORTB.OUT &= ~(1<<trigPinA); // Ensure clean HIGH pulse by providing short LOW pulse first
    _delay_us(5);
    PORTB.OUT |= (1<<trigPinA); // Trigger Pin HIGH for 10 ms (Minimum for HC-SR04)
     _delay_us(10);
    PORTB.OUT &= ~(1<<trigPinA); // Trigger Pin LOW
	
	unsigned short ClockStart = TCA0_GetCount(); // Get counter count as pulse is sent
	
	while (!paAIoc) {} // Wait for pb5Ioc to go High

	unsigned short ClockEnd = TCA0_GetCount();

	// Convert the time into a distance
	float cm= (((ClockEnd-ClockStart)*Int_Freq) / 2) / 29.1;     // Divide by 29.1 or multiply by 0.0343

	/* Reset Interrupt Flag */
	paAIoc = 0;

	return cm;
}

float getDistanceB() {
	PORTB.OUT &= ~(1<<trigPinB); // Ensure clean HIGH pulse by providing short LOW pulse first
    _delay_us(5);
    PORTB.OUT |= (1<<trigPinB); // Trigger Pin HIGH for 10 ms (Minimum for HC-SR04)
     _delay_us(10);
    PORTB.OUT &= ~(1<<trigPinB); // Trigger Pin LOW
	
	unsigned short ClockStart = TCA0_GetCount(); // Get counter count as pulse is sent
	
	while (!paBIoc) {} // Wait for pb5Ioc to go High

	unsigned short ClockEnd = TCA0_GetCount();

	// Convert the time into a distance
	float cm= (((ClockEnd-ClockStart)*Int_Freq) / 2) / 29.1;     // Divide by 29.1 or multiply by 0.0343

	/* Reset Interrupt Flag */
	paBIoc = 0;

	return cm;
}


void loop(void) {
    

	float DistanceA = getDistanceA(); // in cm

	float DistanceB = getDistanceB(); // in cm


}

int main(void) {
    
	AppInit();
    for(;;) loop();

}
