.syntax unified
.global _start

_start:
  ldr sp, =_stack
  bl init
  bl main

_exit :
  b _exit
