/**
 * main (entrypoint) implementation
 */
#include "init.h"
#include "pinmap.h"

volatile long Counter;
volatile long duration, cm, inches; // Make Note

void delay (long n) {          // Delay by n milliseconds
	Counter = 469 * n;
	do Counter--; while (Counter != 0);
}

void loop(void) {

    PORTB.OUT &= ~(1<<trigPin); // Ensure clean HIGH pulse by providing short LOW pulse first
    delay(5);
    PORTB.OUT |= (1<<trigPin); // Trigger Pin HIGH for 10 ms (Minimum for HC-SR04)
    delay(10);
    PORTB.OUT &= ~(1<<trigPin); // Trigger Pin LOW

	//TODO: Add PulseIn Here:
	
	
    // Convert the time into a distance
    cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
    inches = (duration/2) / 74;   // Divide by 74 or multiply by 0.0135


}

int main(void) {
    AppInit();
    for(;;) loop();
}
