#ifndef UART_H
#define UART_H

#include<stdint.h>

//Rather than include stdlib.h.
typedef unsigned int size_t;


/*
 * Initializes the USART1 output.
 * Resets USART1 registers and sets :
 * MODE = 8N1
 * Oversampling = 16
 * Speed = 115200 bauds
 */
void uart_init(void);


/*
 * Write a single character on the USART1 output.
 */
void uart_putchar(uint8_t);


/*
 * Write the string s on the USART1 output.
 * Add a final '\n\r' to the output.
 */
void uart_puts(const uint8_t *);

/*
 * Reads one character from USART1 and returns it.
 * If an overrun or a framing error happens, it will
 * go for an infite loop.
 */
uint8_t uart_getchar(void);

/*
 * Reads at most size - 1 characters from USART1 and puts them
 * in the buffer s. It ends if a \n or \r is read.
 * A final nul ('\0') byte is put at the end of the line.
 *
 * If an overrun or a framing error happens, it will
 * go for an infite loop.
 */
void uart_gets(uint8_t *, size_t);

#endif
