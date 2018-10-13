#include "led.h"
#include "clocks.h"
#include "uart.h"

int fibo(int);
void led_trial(void);

int main(){
  clocks_init();
  uart_init();
  char c = 'A';
  for (int i=0; i<10; i++){
    uart_putchar((uint8_t)(c+i));
  }
  //led_trial();
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

void led_trial(){
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
