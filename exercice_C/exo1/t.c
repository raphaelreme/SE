#include <stdint.h>
#include <stdio.h>

/*DATA*/
int32_t x = 34;
int8_t x8_tab[3] = {0,1,2};
int16_t x16_tab[3] = {0,1,2};
int32_t x32_tab[3] = {0,1,2};
int64_t x64_tab[3] = {0,1,2};

/*COM*/
int64_t y64;
int32_t y32;
int16_t y16;
int8_t y8;

char y_char;
short y_short;
int y_int;
long y_long;
double y_double;

int8_t y8_tab_taille20[20];
int16_t y16_tab_taille20[20];
int32_t y32_tab_taille20[20];
int64_t y64_tab_taille20[20];

int8_t y8_tab_taille10[10];
int16_t y16_tab_taille10[10];
int32_t y32_tab_taille10[10];
int64_t y64_tab_taille10[10];

int8_t* y8_pointeur;
int16_t* y16_pointeur;
int32_t* y32_pointeur;
int64_t* y64_pointeur;


/*RODATA*/
const int8_t z8 = 2;
const int16_t z16 = 2;
const int32_t z32 = 2;
const int64_t z64 = 2;

int main() {
  static uint8_t z;
  uint16_t t;
  y32 = 12;
  z = z + 1;
  t = y32+z;
  printf("x = %ld, y = %ld, z = %d, t = %d\n",x, y32, z, t);
  return 0;
}
