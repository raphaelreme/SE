ldr r1,=a
ldr r1, [r1]
bl f

end:
  b end

f:
  mov r0, #0x00

  loop:
    cmp r0,r1
    bxgt lr @fin du for et donc de f.
    bl g
    add r0,r0,#0x01
    b loop
