/**
 * Pin mapping definitions
 */
#ifndef _PINMAP_H_
#define _PINMAP_H_



#define trigPin (6) // Trigger Pin for HC-SR04
#define echoPin (5) // Echo Pin for HC-SR04
#define PB5_INTERRUPT PORTB.INTFLAGS & PIN5_bm
#define PB5_CLEAR_INTERRUPT_FLAG PORTB.INTFLAGS &= PIN5_bm


#endif /* _PINMAP_H_ */
