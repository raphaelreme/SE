MEMORY
{
  rom (rx) : ORIGIN = 0, LENGTH = 1M
  ram1 (wx): ORIGIN = 0x20000000, LENGTH = 96K
  ram2 (wx): ORIGIN = 0x10000000, LENGTH = 32K
}

ENTRY(_start)

_stack =  ORIGIN(ram2) + LENGTH(ram2) ;

SECTIONS
{
  INTERUPT_TABLE : {
  } > rom

  .text : AT (ADDR(INTERUPT_TABLE)+SIZEOF(INTERUPT_TABLE)){
      _text = . ;
      EXCLUDE_FILE (*crt0.o *init.o) *(.text*)
      _etext = . ;
  } > ram1

  .flashtext (LOADADDR(.text)+SIZEOF(.text)): AT (LOADADDR(.text)+SIZEOF(.text)){
      *(.text*)
  } > rom

  .rodata : {
      *(.rodata*)
      _data_lma = . ;
  } > rom

  .data : AT (LOADADDR(.rodata)+SIZEOF(.rodata)){
      _data = . ;
      *(.data*)
      _edata = . ;
  } > ram1

  .bss : {
      _bss = . ;
	    *(*bss*) *(*COM*)
      _ebss = . ;
  } > ram1
}

  _text_lma = LOADADDR(.text) ;
