#include "led.h"

void led_init(){
  REG_clock_port = REG_clock_port | (1<<1);
  GPIOB_MODER = (GPIOB_MODER & ~(0x3<<28)) | (1<<28);
}

void led_g_on(){
  GPIOB_BSRR = GPIOB_BSRR | (1<<14);
}

void led_g_off(){
  GPIOB_BSRR = GPIOB_BSRR | (1<<30);
}
