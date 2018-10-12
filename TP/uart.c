#include "uart.h"
#include "stm32l475xx.h"
#include "stm32l4xx.h"


void uart_init(){
  //Ena clock of port B
  SET_BIT(RCC->AHB2ENR,RCC_AHB2ENR_GPIOBEN);

  //set alternative fuction mode for TX and RX
  MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODE6_Msk, GPIO_MODER_MODE6_1);
  MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODE7_Msk, GPIO_MODER_MODE7_1);

  //Set the function to AF7 for both of them
  MODIFY_REG(GPIOB->AFRL,GPIO_AFRL_AFSEL6_Msk|GPIO_AFRL_AFSEL7_Msk, (~GPIO_AFRL_AFSEL6_3)|(~GPIO_AFRL_AFSEL7_3));

  //Ena the clock of USART1
  USART1->CR1
  
}
