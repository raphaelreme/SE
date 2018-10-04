#include <stdint.h>
#include <stdio.h>

int32_t x = 34;
int32_t y32;
int16_t y16;
int8_t y8;
int64_t y64;
int y_int;
short y_short;
char y_char;
long y_long;
double y_double;


const char mesg[] = "Hello World!";

int main() {
  static uint8_t z;
  uint16_t t;
  y32 = 12;
  z = z + 1;
  t = y32+z;
  printf(mesg);
  printf("x = %ld, y = %ld, z = %d, t = %d\n",x, y32, z, t);
  return 0;
}
