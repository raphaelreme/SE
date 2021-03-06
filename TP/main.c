#include "main.h"
#include "clocks.h"
#include "led.h"
#include "irq.h"
#include "buttons.h"
#include "matrix.h"
#include "uart.h"

void wait(int n) {
  for (int j=0; j<n; j++) {
    asm volatile("nop");
  }
}

int main() {
  clocks_init();
  led_init();
  irq_init();
  button_init();
  matrix_init();
  uart_init(38400);
  display_frame(frame_buffer);
}
