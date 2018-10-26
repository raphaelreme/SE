#include<stdint.h>

extern uint8_t _bss, _ebss, _data, _edata, _data_lma;

void init(){
  uint8_t* begin = &_bss;
  uint8_t* end = &_ebss;

  while (begin<end){
    *begin = 0;
    begin++;
  }
  return;
}
