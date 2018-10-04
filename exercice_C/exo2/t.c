#include<stdio.h>

int BSS;
int DATA = 1;
const int RODATA = 20;


int main(){
  int i = 3;



  printf("Adresse de BSS : %p\n", &BSS);
  printf("Adresse de DATA : %p\n", &DATA);
  printf("Adresse de RODATA : %p\n", &RODATA);
  printf("Adresse de i : %p\n",  &i);



}
