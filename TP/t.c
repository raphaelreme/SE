#include "led.h"

int fibo(int);

int main(){
  //return fibo(8);
  led_init();
  for (int i=0; i<15;i++){
    for (int j=0; j<100000; j++){
      asm volatile("nop");
    }
    led_g_on();
    for (int j=0; j<100000; j++){
      asm volatile("nop");
    }
    led_g_off();
  }
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
