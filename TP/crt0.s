.cpu cortex-m4
.syntax unified
.global _start

  .thumb_func
_start:
  ldr sp, =_stack
  bl init
  bl main

_exit :
  b _exit
