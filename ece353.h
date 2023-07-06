#ifndef __ECE353_H__
#define __ECE353_H__

#include <stdbool.h>
#include <stdint.h>
#include "msp.h"

//author: Brian Huang

void ece353_led1_init(void);

void ece353_button1_init(void);

void ece353_led1(bool on);

bool ece353_button1(void);

void ece353_RGB_LED_Init(void);

void ece353_RGB_LED(bool red_on, bool green_on, bool blue_on);

void ece353_button2_init(void);

bool ece353_button2(void);

void ece353_T32_1_wait(uint32_t ticks);

/*****************************************************
 * Busy waits for 100mS and then returns.
 *
 * Timer32_1 MUST be configured as a 16-bit timer.
 * Assume that the MCU clock runs at 3MHz.  You will
 * need to use a pre-scalar in order to achieve a delay
 * of 100mS.
 *
 * Parameters:
 *      None
 * Returns
 *      None
 *****************************************************/
void ece353_T32_1_wait_100mS(void);


/*****************************************************
 * Debounces Button1 using Timer32_1.
 * This function does not return until Button 1 has
 * been pressed for a minimum of 5 seconds.
 *
 * Waiting 5 Seconds will require you to call
 * ece353_T32_1_wait_100mS multiple times.
 *
 * Parameters
 *      None
 * Returns
 *      None
 *****************************************************/
void ece353_button1_wait_for_press(void);

void ece353_MKII_S1_Init(void);

void ece353_MKII_S2_Init(void);

bool ece353_MKII_S1(void);

bool ece353_MKII_S2(void);

void ece353_MKII_Buzzer_Init(uint16_t ticks_period);

void ece353_MKII_Buzzer_On(void);

void ece353_MKII_Buzzer_Off(void);

bool ece353_MKII_Buzzer_Run_Status(void);

/*****************************************************
 * Initialize the 3 GPIO pins that control the RGB
 * LED on the MKII.
 *
 * Parameters
 *      en_primary_function  - If set to true, enable the primary function
 *
 * Returns
 *      None
 *****************************************************/
void ece353_MKII_RGB_IO_Init(bool en_primary_function);
/*****************************************************
 * Sets the PWM levels for the MKII RGBLED
 *
 * Parameters
 *      ticks_period    :   Period of PWM Pulse
 *      ticks_red_on    :   Number of Ticks RED is on
 *      ticks_green_on  :   Number of Ticks GREEN is on
 *      ticks_blue_on   :   Number of Ticks BLUE is on
 * Returns
 *      None
 *****************************************************/
void ece353_MKII_RGB_PWM(
        uint16_t ticks_period,
        uint16_t ticks_red_on,
        uint16_t ticks_green_on,
        uint16_t ticks_blue_on
);

void ece353_T32_1_Interrupt_Ms(uint16_t ms);

void ece353_T32_2_Interrupt_Ms(uint16_t ms);

void ece353_ADC14_PS2_X(void);

void ece353_ADC14_PS2_XY(void);

void ece353_MKII_RGB_LED(bool red, bool green, bool blue);

void ece353_ADC14_PS2_XY_COMP(void);

#endif
