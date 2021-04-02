/**
 * Global variable implementation file. Execise care in use!
 */

#include "init.h"
#include "pinmap.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "stdint.h"
#include "bit_utils.h"

volatile uint8_t pb5Ioc;