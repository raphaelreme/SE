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
 * Speed = baudrate
 *
 * It also enables interuptions when there is something to read.
 */
void uart_init(int baudrate);


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

/*
 * Usart handler. used for reading from usart1.
 * It adds the char received to frame.
 * Any frame has to start with 0xff (will not be added to frame)
 * When 0xff is received, the frame is set to 0 and the receiver wait a maximum
 * of 192 char. Then receiver wait a new frame.
 *
 *
 * If an ORE or FE occured, it will wait the next frame.
 * NE is ignored.
 * And the other interuptions are treated with the default handler of irq.c.
 */
void USART1_IRQHandler(void);

#endif
