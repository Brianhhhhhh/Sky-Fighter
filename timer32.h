//author: Brian Huang


#ifndef TIMER32_H_
#define TIMER32_H_

#include "msp.h"
#include <stdbool.h>
#include <stdint.h>
#include "main.h"

extern volatile bool screen_update;

void T32_INI2(void);
void T32_INT2_IRQHandler(void);
#endif /* TIMER32_H_ */
