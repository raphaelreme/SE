#include "led.h"
#include "clocks.h"

int fibo(int);

int main(){
  clocks_init();
  led_init();

  for (int i=0; i<15;i++){
    for (int j=0; j<1000000; j++){
      asm volatile("nop");
    }
    led(LED_OFF);
    led_g_on();
    for (int j=0; j<1000000; j++){
      asm volatile("nop");
    }
    led_g_off();
    led(LED_YELLOW);
    for (int j=0; j<1000000; j++){
      asm volatile("nop");
    }
    led(LED_BLUE);
  }
  led(LED_OFF);
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
