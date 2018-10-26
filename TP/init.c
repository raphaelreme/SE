#include<stdint.h>

extern uint8_t _bss, _ebss, _data, _edata, _data_lma, _text, _etext, _text_lma;

void init() {
  uint8_t* dst = &_bss;
  //init bss
  while (dst < &_ebss) {
    *dst = 0;
    dst++;
  }

  //copy .text section
  uint8_t* src = &_text_lma;

  for (dst = &_text; dst < &_etext; dst++) {
    *dst = *src;
    src++;
  }

  //copy .data section
  src = &_data_lma;

  for (dst = &_data; dst < &_edata; dst++) {
    *dst = *src;
    src++;
  }

  return;
}
