#ifndef LED_H
#define LED_H

#include <stdint.h>

enum state {LED_OFF, LED_YELLOW, LED_BLUE};

void led_init(void);
void led_g_on(void);
void led_g_off(void);
void led(enum state);

#endif
