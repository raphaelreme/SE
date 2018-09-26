

bl f

end:
  b end

f:
  ldr r1,=a
  ldr r2,=b
  ldr r3,=c
  ldr r0, [r1]
  ldr r1, [r2]
  ldr r2, [r3]

  ldr r3, [r0]
  ldr r5, [r2]
  add r4, r3, r5
  str r4, [r0]

  ldr r4, [r1]
  add r3, r4, r5
  str r3, [r1]

  bx lr
