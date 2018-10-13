#ifndef UART_H
#define UART_H
#include<stdint.h>

void uart_init(void);

void uart_putchar(uint8_t);
void uart_puts(const uint8_t *);

uint8_t uart_getchar(void);
void uart_gets(uint8_t *, size_t);

#endif
