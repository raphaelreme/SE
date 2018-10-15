#include "clocks.h"
#include "matrix.h"

static void test_pixel(void);

void wait(int n){
  for (int j=0; j<n; j++){
    asm volatile("nop");
  }
}

int main(){
  clocks_init();
  matrix_init();
  test_pixel();
}


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
