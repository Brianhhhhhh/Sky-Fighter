//author: Brian Huang


#ifndef TASK_BUTTON_H_
#define TASK_BUTTON_H_

#include "main.h"

typedef enum {S1, S2} BUTTON_TYPE;

typedef struct {
    BUTTON_TYPE button;
}BUTTON_MSG_t;

extern QueueHandle_t Queue_BUTTON;



/******************************************************************************
* Controls the RGB LED on the MKII
******************************************************************************/
void Task_BUTTON(void *pvParameters);

static void add_enemy(void);

static void bullet_shot(void);




#endif /* TASK_BUTTON_H_ */
