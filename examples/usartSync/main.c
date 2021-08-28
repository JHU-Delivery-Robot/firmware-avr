#define F_CPU 3333333
#define USART0_BAUD_RATE(BAUD_RATE) ((float)(F_CPU / (2 * (float)BAUD_RATE)) + 0.5)
#define USART1_BAUD_RATE(BAUD_RATE) ((float)(F_CPU / (2 * (float)BAUD_RATE)) + 0.5)

#include <avr/io.h>
#include <avr/interrupt.h>

volatile char x;

void USART0_syncInit(void);
// void USART1_syncInit(void);
void USART0_syncWrite(char data);
void USART0_syncWrite(char data);

ISR(USART0_RXC_vect)
{
    x = USART0.RXDATAL;
    /* Set a breakpoint on the NOP below to check the value of x in the debugger */
    // asm("NOP");
}

// ISR(USART1_RXC_vect)
// {
//     x = USART1.RXDATAL;
//     /* Set a breakpoint on the NOP below to check the value of x in the debugger */
//     asm("NOP");
// }

void USART0_syncInit(void)
{
    PORTB.DIR &= ~PIN3_bm; // rx
    PORTB.DIR |= PIN2_bm; // tx
    PORTB.DIR |= PIN1_bm; // xck

    
    
    USART0.CTRLA |= USART_RXCIE_bm;  
    USART0.CTRLB |= USART_RXEN_bm | USART_TXEN_bm;  
    USART0.CTRLC |= USART_CMODE_SYNCHRONOUS_gc;
}

// void USART1_syncInit(void)
// {
//     PORTC.DIR &= ~PIN1_bm;
//     PORTC.DIR |= PIN0_bm;
//     PORTC.DIR &= ~PIN2_bm;
    
//     USART1.CTRLA |= USART_RXCIE_bm; 
//     USART1.CTRLB |= USART_RXEN_bm | USART_TXEN_bm;    
//     USART1.CTRLC |= USART_CMODE_SYNCHRONOUS_gc; 
// }

void USART0_syncWrite(char data)
{
    while (!(USART0.STATUS & USART_DREIF_bm))
    {
        ;
    }
    USART0.TXDATAL = data;
}

// void USART1_syncWrite(char data)
// {
//     while (!(USART1.STATUS & USART_DREIF_bm))
//     {
//         ;
//     }        
//     USART1.TXDATAL = data;
// }

int main(void)
{   
    USART0_syncInit();
    // USART1_syncInit();
    
    /* Enable global interrupts */
    sei();
    
    while (1) 
    {
        USART0_syncWrite('A');
        // USART1_syncWrite('B');
    }
}