#include "led.h"
#include "clocks.h"
#include "uart.h"

int fibo(int);
void leds(void);
void test_puts(void);
void test_getchar(void);
void test_gets(void);
void check_sum(void);

void hexa(uint8_t *, uint32_t);


/********************************************************************/
/****************Size of the data send by checksum*******************/
static const size_t SIZE = 10000;



void wait(int n){
  for (int j=0; j<n; j++){
    asm volatile("nop");
  }
}

int main(){
  clocks_init();
  uart_init();
  wait(10000);

  check_sum();
}

void leds(){
  const int WAIT = 3000000;
  const int NB = 10;

  led_init();

  for (int i=0; i<NB; i++){
    wait(WAIT);
    led(LED_OFF);
    led_g_on();

    wait(WAIT);
    led_g_off();
    led(LED_YELLOW);

    wait(WAIT);
    led(LED_BLUE);
  }
  led(LED_OFF);
}

void test_puts(){
  char c = 'A';
  const uint8_t * chaine = (const uint8_t *)"Hello world";

  for (int i=0; i<10; i++){
    uart_putchar((uint8_t)(c+i));
  }
  uart_puts(chaine);
}

void test_getchar(){
  for (int i=0; i<1000; i++){
    uart_putchar(uart_getchar());
  }
}

void test_gets(){
  size_t size = 11;
  int8_t tab[size];
  while(1){
    uart_puts((const uint8_t *)"Enter 10 characters :");
    uart_gets((uint8_t *)tab, size);
    uart_puts((uint8_t *)tab);
  }
}

void check_sum(){
  uint32_t sum = 0;
  uint8_t s[11];

  for (uint32_t i=0; i<SIZE; i++){
    sum += uart_getchar();
  }

  uart_puts((const uint8_t *)"Sum :");

  hexa((uint8_t *)s, sum);
  uart_puts((uint8_t *)s);
}

/*
 * Return the hexadicmal form of integer in a string.
 */
void hexa(uint8_t * s, uint32_t value){
  const uint8_t c[16] = "0123456789abcdef";

  s[0] = '0';
  s[1] = 'x';

  for (int i=9; i>1;i--){
    s[i] = c[value%16];
    value /= 16;
  }
  s[10] = 0;
}
