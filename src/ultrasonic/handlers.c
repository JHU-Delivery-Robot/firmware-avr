/**
 * ISR handler implementation file
 */
#include "handlers.h"
#include "init.h"
#include "pinmap.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "stdint.h"
#include "bit_utils.h"
#include "globals.h"



ISR(PORTB_PORT_vect)
{
	if(PB5_INTERRUPT)
	{
		pb5Ioc = 1;
		PB5_CLEAR_INTERRUPT_FLAG;
	}
}