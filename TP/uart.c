#include "uart.h"
#include "stm32l475xx.h"
#include "stm32l4xx.h"


void uart_init(){
  //Ena clock of port B
  SET_BIT(RCC->AHB2ENR,RCC_AHB2ENR_GPIOBEN);

  //set alternative fuction mode for TX and RX
  MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODE6_Msk|GPIO_MODER_MODE7_Msk, GPIO_MODER_MODE6_1|GPIO_MODER_MODE7_1);
  //MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODE7_Msk, GPIO_MODER_MODE7_1);

  //Set the function to AF7 for both of them
  MODIFY_REG((GPIOB->AFR)[0], GPIO_AFRL_AFSEL6_Msk|GPIO_AFRL_AFSEL7_Msk, 0x7<<GPIO_AFRL_AFSEL6_Pos|0x7<<GPIO_AFRL_AFSEL7_Pos);

  //Ena the clock of USART1
  SET_BIT(RCC->APB2ENR, RCC_APB2ENR_USART1EN);

  //PCLK selected as USART1 clock
  CLEAR_BIT(RCC->CCIPR, RCC_CCIPR_USART1SEL);

  //Reset USART1
  SET_BIT(RCC->APB2RSTR, RCC_APB2RSTR_USART1RST);
  CLEAR_BIT(RCC->APB2RSTR, RCC_APB2RSTR_USART1RST);


  //Set baud rate to 115 200 -> it depends on the clock (here clock = 80MHz)
  //80Mhz/115200 = 694.44
  USART1->BRR = 694;

  //Configure CR1 and CR2 -> 8N1 and oversampling to 16
  //Useless as the reset has alreadey set them all to 0
  CLEAR_BIT(USART1->CR1, USART_CR1_OVER8 | USART_CR1_M1 | USART_CR1_M | USART_CR1_PCE);
  CLEAR_BIT(USART1->CR2, USART_CR2_STOP);

  SET_BIT(USART1->CR1, USART_CR1_TE | USART_CR1_RE | USART_CR1_UE);
}

void uart_putchar(uint8_t c){
  while (READ_BIT(USART1->ISR, USART_ISR_TXE) == 0){}
  USART1->TDR = c;
}

uint8_t uart_getchar(){
  while (READ_BIT(USART1->ISR, USART_ISR_RXNE) == 0){}
  return (uint8_t)READ_BIT(USART1->RDR, 0xff);
}
