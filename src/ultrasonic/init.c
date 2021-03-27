/**
 * System initialization functions implementation
 */
#include "init.h"
#include "pinmap.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "stdint.h"
#include "bit_utils.h"

void AppInit() {
    
    PORTB.DIR = 0x00; // Set all pins to input mode, including echoPin
    PORTB.DIR = (1<<trigPin); // Set trigPin to output mode
    
}
