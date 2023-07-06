//author: Brian Huang

#include "timer32.h"
#include "ece353.h"

volatile bool screen_update = false;

uint8_t button_state = 0x00;

/*
 * Configure Timer32_2 to generate an interrupt every 100mS
 */
void T32_INI2(){
    ece353_T32_2_Interrupt_Ms(15);

}

void T32_INT2_IRQHandler()
{
    //send out the alert that LCD can be updated
    screen_update = true;

    //clear the interrupt
    TIMER32_2->INTCLR = BIT0;

}
