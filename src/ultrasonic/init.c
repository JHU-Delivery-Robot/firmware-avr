/**
 * System initialization functions implementation
 */
#include "init.h"

void AppInit() {
    
    PORTB.DIR = 0x00; // Set all pins to input mode, including echoPin
    PORTB.DIR = (1<<trigPin); // Set trigPin to output mode
    
}
