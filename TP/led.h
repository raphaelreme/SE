#ifndef LED_H
#define LED_H

#include <stdint.h>

#define CLOCK_ENA (*(volatile uint32_t *)0x4002104c)

#define GPIOB_MODER (*(volatile uint32_t *)0x48000400)
#define GPIOB_BSRR (*(volatile uint32_t *)0x48000418)

#define GPIOC_MODER (*(volatile uint32_t *)0x48000800)
#define GPIOC_BSRR (*(volatile uint32_t *)0x48000818)

enum state {LED_OFF, LED_YELLOW, LED_BLUE};


void led_init(void);
void led_g_on(void);
void led_g_off(void);
void led(enum state);

#endif
