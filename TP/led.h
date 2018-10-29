#ifndef LED_H
#define LED_H

#include <stdint.h>

enum state {LED_OFF, LED_YELLOW, LED_BLUE};

/*
 * Initializes the leds green, blue and yellow (PB14 and PC9).
 */
void led_init(void);

/*
 * Turn on/off the green light
 */
void led_g_on(void);
void led_g_off(void);

/*
 * Used to turn on/off the leds blue or yellow (PC9).
 */
void led(enum state);

#endif
