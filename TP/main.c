#include "clocks.h"
#include "matrix.h"

extern uint8_t _binary_image_raw_start;

static void test_pixel(void);
static void test_static_image(void);

void wait(int n){
  for (int j=0; j<n; j++){
    asm volatile("nop");
  }
}

int main(){
  clocks_init();
  matrix_init();
  test_static_image();


  if (0) {test_pixel();}
}


/*
 * Turn on all the leds with enough speed so that
 * human eyes believed them all to be enabled at the same time
 */
static void test_pixel(){
  rgb_color red[8];
  rgb_color green[8];
  rgb_color blue[8];

  for (int i=0; i<8; i++){
    red[i].r = 1<<i;
    red[i].g = 0;
    red[i].b = 0;

    green[i].r = 0;
    green[i].g = 1<<i;
    green[i].b = 0;

    blue[i].r = 0;
    blue[i].g = 0;
    blue[i].b = 1<<i;
  }
  desactivate_rows();

  int i = 0;
  while (1){
    i -= 9*(i==9);
    mat_set_row(i, (rgb_color *)red);
    wait(1000);

    mat_set_row((i+1)%8, (rgb_color *)green);
    wait(1000);

    if (i!=6){
      mat_set_row((i+2)%8, (rgb_color *)blue);
      wait(1000);
    }

    i+=3;
  }
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
