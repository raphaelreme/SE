#include "stm32l475xx.h"
#include "stm32l4xx.h"
#include "buttons.h"
#include "irq.h"
#include "led.h"
#include "main.h"


void button_init() {
  //Ena clock of port C
  SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOCEN);

  //Set input mode for PC13
  CLEAR_BIT(GPIOC->MODER, GPIO_MODER_MODE13_Msk);

  //Enable interupt for falling trigger in line 13
  SET_BIT(EXTI->IMR1, EXTI_IMR1_IM13);
  CLEAR_BIT(EXTI->RTSR1, EXTI_RTSR1_RT13);
  SET_BIT(EXTI->FTSR1, EXTI_FTSR1_FT13);

  //Select PC13 as source for EXTI13
  MODIFY_REG(SYSCFG->EXTICR[3],SYSCFG_EXTICR4_EXTI13_Msk,SYSCFG_EXTICR4_EXTI13_PC);

  // Enable Irq from EXTI10-15
  NVIC_EnableIRQ(40);
}


void EXTI15_10_IRQHandler() {
  if (READ_BIT(EXTI->PR1, EXTI_PR1_PIF13)) {
    //EXTI13 Handler
    SET_BIT(EXTI->PR1, EXTI_PR1_PIF13);
    led_g_on();
    wait(10000000);
    led_g_off();
    return ;
  } else {
    //For the others. Should be unused with the current code.
    default_handler();
  }
}
