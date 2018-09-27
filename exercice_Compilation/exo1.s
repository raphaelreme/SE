bl f

end:
  b end

f:
  ldr r2, =a
  ldr r1, [r2]
  mov r0, #0x00

  loop:
    cmp r0,r1
    bxgt lr @fin du for et donc de f.
    bl g
    ldr r1, [r2]
    add r0,r0,#1
    and r0,r0,#0x000000FF
    b loop
