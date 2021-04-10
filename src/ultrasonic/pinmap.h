/**
 * Pin mapping definitions
 */
#ifndef _PINMAP_H_
#define _PINMAP_H_



#define trigPinA (1) // Trigger Pin for HC-SR04
#define echoPinA (2) // Echo Pin for HC-SR04
#define PA2_INTERRUPT PORTA.INTFLAGS & PIN2_bm
#define PA2_CLEAR_INTERRUPT_FLAG PORTA.INTFLAGS &= PIN2_bm

#define trigPinB (3) // Trigger Pin for HC-SR04
#define echoPinB (4) // Echo Pin for HC-SR04
#define PA4_INTERRUPT PORTA.INTFLAGS & PIN4_bm
#define PA4_CLEAR_INTERRUPT_FLAG PORTA.INTFLAGS &= PIN4_bm
#endif /* _PINMAP_H_ */
