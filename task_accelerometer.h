//author: Brian Huang


#ifndef TASK_ACCELEROMETER_H_
#define TASK_ACCELEROMETER_H_

#include "main.h"

#define VOLT_0P85  1056      // 0.85 /(3.3/4096)
#define VOLT_2P50  3103      // 2.50 /(3.3/4096)

extern TaskHandle_t Task_Accelerometer_Handle;
extern TaskHandle_t Task_Accelerometer_Timer_Handle;


typedef enum {
    ACC_DIR_CENTER,
    ACC_DIR_LEFT,
    ACC_DIR_RIGHT,
    ACC_DIR_UP,
    ACC_DIR_DOWN,
}ACC_DIR_t;

/********************************
* Initialization of Accelerometer
********************************/
void Task_Accelerometer_Init(void);

/******************************************************************************
* Used to start an ADC14 Conversion
******************************************************************************/
void Task_Accelerometer_Timer(void *pvParameters);


/******************************************************************************
* Examines the ADC data from the accelerometer on the MKII
******************************************************************************/
void Task_Accelerometer_Bottom_Half(void *pvParameters);



#endif /* TASK_ACCELEROMETER_H_ */
