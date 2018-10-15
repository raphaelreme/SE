#include "uart.h"
#include "stm32l475xx.h"
#include "stm32l4xx.h"


static void active_wait(){
  while(1){
    asm volatile("nop");
  }
}

/*
 * Initializes the USART1 output.
 * Resets USART1 registers and sets :
 * MODE = 8N1
 * Oversampling = 16
 * Speed = 115200 bauds
 */
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



/*
 * Write a single character on the USART1 output.
 */
void uart_putchar(uint8_t c){
  while (READ_BIT(USART1->ISR, USART_ISR_TXE) == 0){}
  USART1->TDR = c;
}

/*
 * Write the string s on the USART1 output.
 * Add a final '\n\r' to the output.
 */
void uart_puts(const uint8_t *s){
    while(*s != 0){
        uart_putchar(*s);
        s++;
    }
    uart_putchar('\n');
    uart_putchar('\r');
}

/*
 * Reads one character from USART1 and returns it.
 * If an overrun or a framing error happens, it will
 * go for an infite loop.
 */
uint8_t uart_getchar(){
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


/*
 * Reads at most size - 1 characters from USART1 and puts them
 * in the buffer s. It ends if a \n or \r is read.
 * A final nul ('\0') byte is put at the end of the line.
 *
 * If an overrun or a framing error happens, it will
 * go for an infite loop.
 */
void uart_gets(uint8_t *s, size_t size){
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
