/**
 * Global variable implementation file. Execise care in use!
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "init.h"
#include "pinmap.h"
#include "stdint.h"
#include "bit_utils.h"

volatile uint8_t paAIoc;
volatile uint8_t paBIoc;
