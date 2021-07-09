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


float getDistance(int trigPin, int frequency, uint8_t flag) {
	PORTB.OUT &= ~(1<<trigPin); // Ensure clean HIGH pulse by providing short LOW pulse first
    _delay_us(5);
    PORTB.OUT |= (1<<trigPin); // Trigger Pin HIGH for 10 ms (Minimum for HC-SR04)
     _delay_us(10);
    PORTB.OUT &= ~(1<<trigPin); // Trigger Pin LOW
	
	uint16_t ClockStart = TCA0_GetCount(); // Get counter count as pulse is sent
	
	while (!flag) {} // Wait for pb5Ioc to go High

	uint16_t ClockEnd = TCA0_GetCount();

	// Convert the time into a distance
	float cm= (((ClockEnd-ClockStart)*frequency) / 2) * 0.0343;     // Divide by 29.1 or multiply by 0.0343

	/* Reset Interrupt Flag */
	flag = 0;

	return cm;
}


void loop(void) {
    

	float DistanceA = getDistance(trigPinA, Int_Freq, paAIoc); // in cm

	float DistanceB = getDistanceB(trigPinB, Int_Freq, paBIoc); // in cm


	//PORTB.OUT = (short) DistanceA;


}

int main(void) {
    
	AppInit();
    for(;;) loop();

}
