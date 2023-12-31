/*
 * opt3001.c
 *
 *  Created on: Mar 14, 2021
 *      Author: younghyunkim
 */

#include "opt3001.h"
#include "math.h"

/******************************************************************************
 * Initialize the opt3001 ambient light sensor on the MKII.  This function assumes
 * that the I2C interface has already been configured to operate at 100KHz.
 ******************************************************************************/

void opt3001_init(void)
{
    // Initialize OPT3001
    i2c_write_16(OPT3001_SLAVE_ADDRESS, CONFIG_REG, 0xB610);
}


/******************************************************************************
 * Returns the current ambient light in lux
 *  ******************************************************************************/
float opt3001_read_lux(void)
{
    // Read the Result register of OPT3001 and convert into Lux, then return.
    //lux = 0.01 � (2^E[3:0]) � R[11:0]

    uint16_t result = i2c_read_16(OPT3001_SLAVE_ADDRESS, RESULT_REG);

    uint16_t E = result >> 12;
    uint16_t R = result & 0x0FFF;


    return .01 * pow(2, E) * R;

}

