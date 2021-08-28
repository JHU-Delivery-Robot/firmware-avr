/**
 * Timer Control Functions
 */
#ifndef _TIMERCONTROL_H_
#define _TIMERCONTROL_H_

// 20 Mhz
#define F_CPU 20000000
#define PERIOD_VALUE (0xFFFF) // Set Top to (65,535)
#define PRE_SCALER TCA_SINGLE_CLKSEL_DIV256_gc // Set Prescaler to 1/256 Source Clock
#define Int_Freq ( 256 / F_CPU )

/**
 * Prereqs:
 *   [None]
 * Side Effects:
 *   [None]
 * Initializes [TCA0 - normal mode, count up, disable events, disable waveform generation
 * , set period (TOP), clear control register, set prescaler] and STARTS timer.
 * @param 
 * @return Void
 */
void TCA0_init();

/**
 * Prereqs:
 *   [None]
 * Side Effects:
 *   [None]
 * Sets timer TCA enable bit 1, effectively starting the timer/counter.
 * @param 
 * @return Void
 */
void TCA0_Start();

/**
 * Prereqs:
 *   [None]
 * Side Effects:
 *   [None]
 * Sets timer TCA enable bit 0, effectively stopping the timer/counter.
 * @param 
 * @return Void
 */
void TCA0_Stop();

/**
 * Prereqs:
 *   [None]
 * Side Effects:
 *   [None]
 * Clock is stopped. Timer registers are set to their intitial (reset) values.
 * @param 
 * @return Void
 */
void TCA0_Reset();

/**
 * Prereqs:
 *   [None]
 * Side Effects:
 *   [temporarily disables interrupts while reading]
 * Timer clock register values are read.
 * @param 
 * @return Count - The current clock count [0,PERIOD_VALUE (TOP)]. 
 */
uint16_t  TCA0_GetCount();

#endif /* _TIMERCONTROL_H_ */
