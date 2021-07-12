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

ISR(PORTA_PORT_vect) {

	if(PORTA.INTFLAGS & PIN2_bm)
	{
		paAIoc = 1;
		_CLR_BIT(PORTA.INTFLAGS, PIN2_bp);
	}

	if(PORTA.INTFLAGS & PIN4_bm)
	{
		paBIoc = 1;
		_CLR_BIT(PORTA.INTFLAGS, PIN4_bp);
		
	}
}
