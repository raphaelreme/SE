target ext :2331
mon endian little
mon halt

# Define "split" and "ss" commands to switch to different user interface layouts
define split
  layout split
  layout asm
  layout regs
  focus cmd
end

define ss
  layout split
  layout src
  layout regs
  focus cmd
end

# Define "flash" command to reflash processor
define flash
  dont-repeat
  mon reset
  set *0x40022008=0x45670123
  set *0x40022008=0xCDEF89AB
  set *0x40022014=0x40010004
  shell sleep 1
  set *0x40022010=0x000000A0
  mon reset
  set *0x40022008=0x45670123
  set *0x40022008=0xCDEF89AB
  set *0x40022014=0x40000001
  load
  set *0x40022010=0x000000A0
  mon reset
  set $sp=$msp
end
