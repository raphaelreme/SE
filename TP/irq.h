#ifndef IRQ_H
#define IRQ_H


/*
 * Initializes the NVIC.
 * Default handlers for all the interuptions have the behaviour of default_handler.
 */
void irq_init(void);

/*
 * Disable interupts and loop.
 */
void default_handler(void);

 #endif
