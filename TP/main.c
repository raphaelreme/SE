#include "clocks.h"
#include "irq.h"


void wait(int n){
  for (int j=0; j<n; j++){
    asm volatile("nop");
  }
}

int main(){
  clocks_init();
  irq_init();
)
}
