/* Arduino Uno Blink sketch for use with the empty core */

// #define F_CPU 20000000
// #define USART0_BAUD_RATE(BAUD_RATE) ((float)(F_CPU * 64 / (16 * (float)BAUD_RATE)) + 0.5)

// #include <avr/io.h>
// #include <util/delay.h>
// #include <string.h>
// #include <avr/interrupt.h>
// #include "stdint.h"
// #include "bit_utils.h"

// void USART0_init(void);
// void USART0_sendChar(char c);
// void USART0_sendString(char *str);

// void USART0_init(void)
// {
//     PORTC.DIR &= ~PIN1_bm; // Set RxD as Input
//     PORTC.DIR |= PIN0_bm;  // Set txD as Output
    
    

//     USART0.BAUD = (uint16_t)USART0_BAUD_RATE(9600);

//     USART0.CTRLB |= USART_TXEN_bm; // Enable Transmitter
// }

// void USART0_sendChar(char c)
// {
//     while (!(USART0.STATUS & USART_DREIF_bm)) // check if the previous transmission is completed by checking the USARTn.STATUS register
//     {
//         ;
//     }        
//     USART0.TXDATAL = c;
// }

// void USART0_sendString(char *str)
// {
//     for(size_t i = 0; i < strlen(str); i++)
//     {
//         USART0_sendChar(str[i]);
//     }
// }

// int main(void)
// {
//     USART0_init();
    
//     while (1) 
//     {
//         USART0_sendString("Hello World!\r\n");
//         _delay_ms(500);
//     }
// }

/*
    Minimal USART test for attiny816
 */ 



// #ifndef F_CPU
// #warning "You haven't defined F_CPU. I'm using F_CPU = 3333333"
#define F_CPU 3333333
// #define F_CPU 20000000
// #define F_CPU 2666666
// #endif
#include <avr/io.h>
#include <assert.h>
#include <util/delay.h>
#include <string.h>
#include <avr/interrupt.h>
#include "stdint.h"
#include "bit_utils.h"
#define BAUD_RATE 9600

#define UROUND(x) ((2UL*(x)+1)/2)
#define USART0_BAUD_RATE(BAUD_RATE) ((float)(F_CPU * 64 / (16 * (float)BAUD_RATE)) + 0.5)

// Set up USART0 in asynchronous mode.
// Default pin locations (i.e. not remaped)
// RX = PB3
// TX = PB2


void usart_init(void)
{
    PORTB.OUTSET = PIN2_bm;
    PORTB.DIRSET = PIN2_bm;
    // USART0.BAUD = UROUND(64UL*F_CPU/16/BAUD_RATE);

    // int8_t sigrow_val = SIGROW.OSC16ERR3V; // Read signed error
    // int32_t baud_reg_val = 9600; // Ideal BAUD register value

    // assert (baud_reg_val >= 0x4A); // Verify legal min BAUD register value
    // baud_reg_val *= (1024 + sigrow_val); // Sum resolution + error
    // baud_reg_val /= 1024; // Divide by resolution
    // USART0.BAUD = (int16_t) baud_reg_val; // Set adjusted baud rate


    USART0.BAUD = (uint16_t)USART0_BAUD_RATE(9600);
    // USART0.CTRLB = USART_RXEN_bm | USART_TXEN_bm;
    USART0.CTRLB |= USART_TXEN_bm; // Enable Transmitter
}

// uint8_t usart_ischar(void)
// {
//     return (USART0.STATUS & USART_RXCIF_bm) != 0;
// }

// char usart_getchar(void)
// {
//     while(!usart_ischar())
//         ;
//     return USART0_RXDATAL;
// }

// void usart_putchar(char ch)
// {
//     while((USART0.STATUS & USART_DREIF_bm) == 0)
//         ;
//     USART0.TXDATAL = ch;
// }

void USART0_sendChar(char c)
{
    while (!(USART0.STATUS & USART_DREIF_bm)) // check if the previous transmission is completed by checking the USARTn.STATUS register
    {
        ;
    }        
    USART0.TXDATAL = c;
}

void USART0_sendString(char *str)
{
    for(size_t i = 0; i < strlen(str); i++)
    {
        USART0_sendChar(str[i]);
    }
}

int main(void)
{
    usart_init();

    while (1)
    {
        while (1) 
    {
        USART0_sendString("1234");
        _delay_ms(500);
    }
        // if (usart_ischar())
        // {
        //     usart_putchar(usart_getchar());
        // }
    }
}