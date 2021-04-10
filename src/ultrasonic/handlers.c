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



ISRA(PORTA_PORT_vect)
{
	if(PA2_INTERRUPT)
	{
		paAIoc = 1;
		PA2_CLEAR_INTERRUPT_FLAG;
	}
}


ISRB(PORTA_PORT_vect)
{
	if(PA4_INTERRUPT)
	{
		paBIoc = 1;
		PA4_CLEAR_INTERRUPT_FLAG;
	}
}