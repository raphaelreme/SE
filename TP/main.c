#include "led.h"
#include "clocks.h"
#include "uart.h"

int fibo(int);
void leds(void);
void test_puts(void);
void test_getchar(void);
void test_gets(void);

void wait(int n){
  for (int j=0; j<n; j++){
    asm volatile("nop");
  }
}

int main(){
  clocks_init();
  uart_init();
  wait(10000);

  test_gets();



}




int fibo(int n){
  if (n<0){
    return -1;
  }
  if (n<2){
    return n;
  }
  return fibo(n-1)+fibo(n-2);
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
