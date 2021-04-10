#include "init.h"
#include "pinmap.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "stdint.h"
#include "bit_utils.h"
#include "globals.h"

#define PERIOD_VALUE (0xFFFF) // Set Top to (65,535)
#define PRE_SCALER TCA_SINGLE_CLKSEL_DIV256_gc


void TCA0_init(void)
{

 /* Set TCA in Normal Mode (CTRLD.SPLITM=0) */
 TCA0.SINGLE.CTRLD = 0;

 /* disable event counting */
 TCA0.SINGLE.EVCTRL &= ~(TCA_SINGLE_CNTEI_bm);

 /* disable waveform generatrion */
 TCA0.SINGLE.CTRLB = 0x0;

 /* set the period */
 TCA0.SINGLE.PER = PERIOD_VALUE;

 /* clear control register comands */
 TCA0.SINGLE.CTRLECLR = TCA_SINGLE_CMD_NONE_gc;

 /* set prescaler and begin clock */
 TCA0.SINGLE.CTRLA = PRE_SCALER /* set clock source (sys_clk/256) */
 | TCA_SINGLE_ENABLE_bm; /* start timer */
}

void TCA0_Start() {

 /* Disable Timer */
 TCA0.SINGLE.CTRLA |= TCA_SINGLE_ENABLE_bm;

}

void TCA0_Stop() {

 /* Disable Timer */
 TCA0.SINGLE.CTRLA &= ~(TCA_SINGLE_ENABLE_bm);

}

void TCA0_Reset() {

 /* ALL timer registers are set to their intitial values */
 /* reset can only be performed when clock is stopped */
 TCA0.SINGLE.CTRLA &= ~(TCA_SINGLE_ENABLE_bm);

 /* force reset */
 TCA0.SINGLE.CTRLESET = TCA_SINGLE_CMD_RESTART_gc;
 
 /* set clock count direction to up */
 TCA0.SINGLE.CTRLESET |= TCA_SINGLE_DIR_UP_gc;

}

unsigned short TCA0_Get() {
    
 /* interrupts may affect reading cycle of 16-bit registers, disable */
 cli();
 
 /* get time from counter register */
 unsigned short time = TCA0.SINGLE.CNT;
 
 /* re-enable interrupts */
 sei();
 
 return time;
}
