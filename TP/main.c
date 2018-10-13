#include "led.h"
#include "clocks.h"
#include "uart.h"

int fibo(int);
void leds(void);

int main(){
  clocks_init();
  uart_init();
  for (int j=0; j<10000; j++){
    asm volatile("nop");
  }

  char c = 'A';
  const uint8_t * chaine = (const uint8_t *)"Hello world";
  for (int i=0; i<10; i++){
    uart_putchar((uint8_t)(c+i));
  }
  uart_puts(chaine);
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
  led_init();

  for (int i=0; i<10;i++){
    for (int j=0; j<3000000; j++){
      asm volatile("nop");
    }
    led(LED_OFF);
    led_g_on();
    for (int j=0; j<3000000; j++){
      asm volatile("nop");
    }
    led_g_off();
    led(LED_YELLOW);
    for (int j=0; j<3000000; j++){
      asm volatile("nop");
    }
    led(LED_BLUE);
  }
  led(LED_OFF);
}
