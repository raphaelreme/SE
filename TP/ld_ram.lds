MEMORY
{
  rom (rx) : ORIGIN = 0, LENGTH = 1M
  ram1 (wx): ORIGIN = 0x20000000, LENGTH = 96K
  ram2 (wx): ORIGIN = 0x10000000, LENGTH = 32K
}

SECTIONS
{
  .text : {
	_start = . ;
	*(.text)
  } > ram1

  .rodata : {
	*(.rodata)
  } > ram1

  .data : {
	*(.data)
  } > ram1

  .bss : {
	*(.bss) *(.COMMON)
  } > ram1
}

ENTRY(_start)
