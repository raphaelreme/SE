#ifndef MATRIX_H
#define MATRIX_H

#include <stdint.h>

#include "stm32l4xx.h"
#include "stm32l475xx.h"

/****************************Turn on/off a row*********************************/
#define ROW0(x)         WRITE_REG(GPIOB->BSRR, (x)?GPIO_BSRR_BS2:GPIO_BSRR_BR2)
#define ROW1(x)         WRITE_REG(GPIOA->BSRR, (x)?GPIO_BSRR_BS15:GPIO_BSRR_BR15)
#define ROW2(x)         WRITE_REG(GPIOA->BSRR, (x)?GPIO_BSRR_BS2:GPIO_BSRR_BR2)
#define ROW3(x)         WRITE_REG(GPIOA->BSRR, (x)?GPIO_BSRR_BS7:GPIO_BSRR_BR7)
#define ROW4(x)         WRITE_REG(GPIOA->BSRR, (x)?GPIO_BSRR_BS6:GPIO_BSRR_BR6)
#define ROW5(x)         WRITE_REG(GPIOA->BSRR, (x)?GPIO_BSRR_BS5:GPIO_BSRR_BR5)
#define ROW6(x)         WRITE_REG(GPIOB->BSRR, (x)?GPIO_BSRR_BS0:GPIO_BSRR_BR0)
#define ROW7(x)         WRITE_REG(GPIOA->BSRR, (x)?GPIO_BSRR_BS3:GPIO_BSRR_BR3)
/****************************Set the correspondig bit**************************/
#define RST(x)          WRITE_REG(GPIOC->BSRR, (x)?GPIO_BSRR_BS3:GPIO_BSRR_BR3)
#define LAT(x)          WRITE_REG(GPIOC->BSRR, (x)?GPIO_BSRR_BS4:GPIO_BSRR_BR4)
#define SB(x)           WRITE_REG(GPIOC->BSRR, (x)?GPIO_BSRR_BS5:GPIO_BSRR_BR5)
#define SCK(x)          WRITE_REG(GPIOB->BSRR, (x)?GPIO_BSRR_BS1:GPIO_BSRR_BR1)
#define SDA(x)          WRITE_REG(GPIOA->BSRR, (x)?GPIO_BSRR_BS4:GPIO_BSRR_BR4)

/****************************Send a 1 on SCK*********************************/
#define pulse_SCK()     do {\
                          SCK(0);  \
                          wait(3); \
                          SCK(1);  \
                          wait(3); \
                          SCK(0);  \
                          }\
                        while (0)

/*****************************Send a 0 on LAT*********************************/
#define pulse_LAT()     do {\
                          LAT(1);  \
                          wait(3); \
                          LAT(0);  \
                          wait(3); \
                          LAT(1);  \
                          }\
                        while (0)



typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} rgb_color;

extern volatile uint8_t frame_buffer[192];


/*
 * Initializes the matrix and wait some times after it.
 * Sets Bank0 value to 0xffffff.
 */
void matrix_init(void);

/*
 * Disables all the rows.
 */
void desactivate_rows(void);

/*
 * Enables the selected rows.
 */
void activate_row(int);

/*
 * Send one byte on SDA on Bank0 or Bank1.
 * Bank != 0 <=> Bank == 1 (It will go on Bank1)
 */
void send_byte(uint8_t, int);

/*
 * Send all the bytes on SDA. Val has to point on 8 rgb_color.
 * It will then disable all the rows and enable the one selected.
 */
void mat_set_row(int, const rgb_color *);

/*
 * Sets Bank0 value to 0xffffff.
 */
void init_bank0();


/*
 * Display the frame
 */
void display_frame(volatile uint8_t *);

#endif
