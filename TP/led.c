#include "led.h"

void led_init(){
  CLOCK_ENA = CLOCK_ENA | (3<<1); //enable port B and C
  GPIOB_MODER = (GPIOB_MODER & ~(0x3<<28)) | (1<<28);
}

void led_g_on(){
  GPIOB_BSRR = 1<<14;
}

void led_g_off(){
  GPIOB_BSRR = 1<<30;
}
