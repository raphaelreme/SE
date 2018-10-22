#include "main.h"
#include "clocks.h"
#include "led.h"
#include "irq.h"
#include "buttons.h"
#include "matrix.h"

extern uint8_t _binary_image_raw_start;

static void test_static_image(void);

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
  test_static_image();
}


/*
 * Display image.raw on the leds.
 * Assume that image.raw has 8*8*3 bytes of data.
 */
static void test_static_image(){
  uint8_t * start = &_binary_image_raw_start;
  while (1){
    for (int i=0; i<8; i++){
      mat_set_row(i, (rgb_color *)(start+i*24));
      wait(1000);
    }
  }
}
