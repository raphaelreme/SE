#include<stdint.h>

extern uint8_t _bss, _ebss, _data, _edata, _data_lma;

void init() {
  uint8_t* dst = &_bss;
  uint8_t* src = &_data_lma;

  while (dst < &_ebss){
    *dst = 0;
    dst++;
  }

  for (dst = &_data; dst < &_edata; dst++){
    *dst = *src;
    src++;
  }
  return;
}
