#include "stm32l475xx.h"
#include "stm32l4xx.h"
#include "uart.h"
#include "irq.h"
#include "matrix.h"



static int index = 0;
static uint8_t has_to_wait = 1;

static void active_wait() {
  while(1) {
    asm volatile("nop");
  }
}


void uart_init(int baudrate) {
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


  //Set baud rate to baudrate -> it depends on the clock (here clock = 80MHz)
  USART1->BRR = 80000000/baudrate;

  //Configure CR1 and CR2 -> 8N1 and oversampling to 16. Enable reading interuption.
  //For CR1 and CR3 0 bits fit, excepts for enable interuption
  //For CR2, 0 is the good value.
  USART1->CR1 = USART_CR1_RXNEIE;
  USART1->CR2 = 0;
  USART1->CR3 = USART_CR3_EIE;

  SET_BIT(USART1->CR1, USART_CR1_TE | USART_CR1_RE | USART_CR1_UE);

  // Enable Irq
  NVIC_EnableIRQ(37);
}



void uart_putchar(uint8_t c) {
  while (READ_BIT(USART1->ISR, USART_ISR_TXE) == 0){}
  USART1->TDR = c;
}


void uart_puts(const uint8_t *s) {
    while(*s != 0){
        uart_putchar(*s);
        s++;
    }
    uart_putchar('\n');
    uart_putchar('\r');
}


uint8_t uart_getchar() {
  do {
    if (READ_BIT(USART1->ISR, USART_ISR_ORE)){
      uart_puts((uint8_t *)"OVERRUN\n");
      active_wait();
    }
    if (READ_BIT(USART1->ISR, USART_ISR_FE)){
      uart_puts((uint8_t *)"FRAMING ERROR\n");
      active_wait();
    }

  } while (READ_BIT(USART1->ISR, USART_ISR_RXNE) == 0);

  return (uint8_t)READ_BIT(USART1->RDR, 0xff);
}



void uart_gets(uint8_t *s, size_t size) {
  uint32_t i;

  for (i=0; i<size-1; i++){
    uint8_t c = uart_getchar();
    s[i] = c;
    if (c == '\n' || c == '\r'){
      i++;
      break;
    }
  }

  s[i]=0;
}


void USART1_IRQHandler() {
  if (READ_BIT(USART1->ISR, USART_ISR_ORE|USART_ISR_FE) != 0) {
    has_to_wait = 1;
    SET_BIT(USART1->ICR, USART_ICR_ORECF|USART_ICR_FECF);
    return;
  }

  if (READ_BIT(USART1->ISR, USART_ISR_NE) != 0) {
    SET_BIT(USART1->ICR, USART_ICR_NECF);
    return;
  }

  if (READ_BIT(USART1->ISR, USART_ISR_RXNE) != 0) {
    uint8_t c = (uint8_t)READ_BIT(USART1->RDR, 0xff);

    if (c == 0xff){
      index = 0;
      has_to_wait = 0;
    } else {
      if (has_to_wait){
        return;
      }
      frame_buffer[index] = c;
      index ++;
      if (index >= 192){
        has_to_wait = 1;
      }
    }
  } else {
    //Should not happen with the current initialization
    default_handler();
  }
}
