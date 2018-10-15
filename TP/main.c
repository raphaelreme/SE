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



}
