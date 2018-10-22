#include "main.h"
#include "clocks.h"
#include "led.h"
#include "irq.h"
#include "buttons.h"
#include "matrix.h"
#include "uart.h"

uint8_t frame[192];


static void display_frame(void);

void wait(int n){
  for (int j=0; j<n; j++){
    asm volatile("nop");
  }
}

int main(){
  clocks_init();
  led_init();
  irq_init();
  button_init();
  matrix_init();
  uart_init(38400);
  display_frame();
}


/*
 * Display the current frame
 */
static void display_frame(){
  
  while (1){
    for (int i=0; i<8; i++){
      mat_set_row(i, (rgb_color *)(frame+i*24));
      wait(1000);
    }
  }
}
