#include "matrix.h"
#include "main.h"


//Only used in initialisation.
#define GPIOA_MODER_Msk GPIO_MODER_MODE2_Msk|GPIO_MODER_MODE3_Msk|GPIO_MODER_MODE4_Msk|GPIO_MODER_MODE5_Msk|GPIO_MODER_MODE6_Msk|GPIO_MODER_MODE7_Msk|GPIO_MODER_MODE15_Msk
#define GPIOA_MODER_0   GPIO_MODER_MODE2_0|GPIO_MODER_MODE3_0|GPIO_MODER_MODE4_0|GPIO_MODER_MODE5_0|GPIO_MODER_MODE6_0|GPIO_MODER_MODE7_0|GPIO_MODER_MODE15_0
#define GPIOB_MODER_Msk GPIO_MODER_MODE0_Msk|GPIO_MODER_MODE1_Msk|GPIO_MODER_MODE2_Msk
#define GPIOB_MODER_0   GPIO_MODER_MODE0_0|GPIO_MODER_MODE1_0|GPIO_MODER_MODE2_0
#define GPIOC_MODER_Msk GPIO_MODER_MODE3_Msk|GPIO_MODER_MODE4_Msk|GPIO_MODER_MODE5_Msk
#define GPIOC_MODER_0   GPIO_MODER_MODE3_0|GPIO_MODER_MODE4_0|GPIO_MODER_MODE5_0

void matrix_init(){
    //Ena clocks of A, B, C
    SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOAEN|RCC_AHB2ENR_GPIOBEN|RCC_AHB2ENR_GPIOCEN);

    //Set the output mode for the needed pins
    MODIFY_REG(GPIOA->MODER, GPIOA_MODER_Msk, GPIOA_MODER_0);
    MODIFY_REG(GPIOB->MODER, GPIOB_MODER_Msk, GPIOB_MODER_0);
    MODIFY_REG(GPIOC->MODER, GPIOC_MODER_Msk, GPIOC_MODER_0);

    //Initializes the value of RST, LAT, SB, SCK and SDA
    WRITE_REG(GPIOC->BSRR, GPIO_BSRR_BR3 | GPIO_BSRR_BS4 | GPIO_BSRR_BS5);
    WRITE_REG(GPIOB->BSRR, GPIO_BSRR_BR1);
    WRITE_REG(GPIOA->BSRR, GPIO_BSRR_BR4);

    //Initializes C0 to C7
    WRITE_REG(GPIOA->BSRR, GPIO_BSRR_BR2 | GPIO_BSRR_BR3 | GPIO_BSRR_BR5 | GPIO_BSRR_BR6 | GPIO_BSRR_BR7 | GPIO_BSRR_BR15);
    WRITE_REG(GPIOB->BSRR, GPIO_BSRR_BR0 | GPIO_BSRR_BR2);

    wait(10000);
    WRITE_REG(GPIOC->BSRR, GPIO_BSRR_BS3);
    init_bank0();
}


void desactivate_rows(){
  ROW0(0);
  ROW1(0);
  ROW2(0);
  ROW3(0);
  ROW4(0);
  ROW5(0);
  ROW6(0);
  ROW7(0);
}


void activate_row(int row){
  switch (row) {
    case 0:
      ROW0(1);
      break;
    case 1:
      ROW1(1);
      break;
    case 2:
      ROW2(1);
      break;
    case 3:
      ROW3(1);
      break;
    case 4:
      ROW4(1);
      break;
    case 5:
      ROW5(1);
      break;
    case 6:
      ROW6(1);
      break;
    case 7:
      ROW7(1);
      break;
  }
}


void send_byte(uint8_t val, int bank){
  SB(bank);
  for (int i=bank?7:5; i>=0; i--){
    SDA(val & (1<<i));
    pulse_SCK();
  }
}

void mat_set_row(int row, const rgb_color *val){
  desactivate_rows();
  for (int i=7; i>=0; i--){
    send_byte(val[i].b, 1);
    send_byte(val[i].g, 1);
    send_byte(val[i].r, 1);
  }
  pulse_LAT();
  wait(100);
  activate_row(row);
}

void init_bank0(){
  for (int i=0; i<24; i++){
    send_byte(0xff,0);
  }
  pulse_LAT();
}
