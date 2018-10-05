#include<stdint.h>


extern uint32_t _bss, _ebss;

void init(){
  uint32_t* begin = &_bss;
  uint32_t* end = &_ebss;

  while (begin<end){
    *begin = 0;
    begin++;
  }
  return;
}
