#ifndef BUTTONS_H
#define BUTTONS_H
/*
 * Initializes interrupt for the blue button.
 * Interupt is raised on falling trigger.
 */
void button_init(void);

/*
 * Handler for EXTI 10 to 15. It only has a specific behaviour for EXT13.
 * For the others it calls the default handler from irq.h. 
 */
void EXTI15_10_IRQHandler(void);

#endif
