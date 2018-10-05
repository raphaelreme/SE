#include<stdio.h>
#include<stdlib.h>

int BSS = 0;
int DATA = 1;
const int RODATA = 20;



void pile(int n){
  if (n>10){
    return;
  }
  printf("Appelle de f numero %d. Adresse de l'argument : %p\n",n,&n);
  pile(n+1);
  return;
}


int main(){
  int* HEAP = (int*) malloc(sizeof(int));
  int* HEAP2 = (int*) malloc(sizeof(int));

  printf("Adresse de TEXT   : %p\n", main);
  printf("Adresse de RODATA : %p\n", &RODATA);
  printf("Adresse de DATA   : %p\n", &DATA);
  printf("Adresse de BSS    : %p\n", &BSS);
  printf("Adresse de HEAP   : %p\n", HEAP);
  printf("Adresse de HEAP2  : %p\n", HEAP2);
  
  pile(1);
}
