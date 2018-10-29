#include "led.h"
#include "stm32l475xx.h"
#include "stm32l4xx.h"


void led_init() {
  //Ena port B and C
  SET_BIT(RCC->AHB2ENR,RCC_AHB2ENR_GPIOBEN | RCC_AHB2ENR_GPIOCEN);
  //Set output mode for B
  MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODE14_Msk, GPIO_MODER_MODE14_0);
  //Set input mode for C (-> the two leds are off)
  CLEAR_BIT(GPIOC->MODER,GPIO_MODER_MODE9_Msk);
}


void led_g_on() {
  WRITE_REG(GPIOB->BSRR, GPIO_BSRR_BS14);
}


void led_g_off() {
  WRITE_REG(GPIOB->BSRR, GPIO_BSRR_BR14);
}


void led(enum state s) {
  if (s==LED_OFF){
    CLEAR_BIT(GPIOC->MODER,GPIO_MODER_MODE9_Msk);
    return;
  }
  //output mode -> one of the led will turn on !
  MODIFY_REG(GPIOC->MODER, GPIO_MODER_MODE9_Msk, GPIO_MODER_MODE9_0);
  if (s==LED_YELLOW){
    WRITE_REG(GPIOC->BSRR, GPIO_BSRR_BS9);
    return;
  }
  //state == LED_BLUE
  WRITE_REG(GPIOC->BSRR, GPIO_BSRR_BR9);
}
