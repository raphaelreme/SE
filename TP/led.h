#ifndef LED_H
#define LED_H

#include <stdint.h>

#define REG_clock_port (*(volatile uint32_t *)0x4002104c)
#define GPIOB_MODER (*(volatile uint32_t *)0x48000400)
#define GPIOB_BSRR (*(volatile uint32_t *)0x48000418)


void led_init(void);
void led_g_on(void);
void led_g_off(void);

#endif
