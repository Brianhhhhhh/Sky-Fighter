//author: Brian Huang


#ifndef TASK_MKII_S1_H_
#define TASK_MKII_S1_H_

#include "main.h"

extern TaskHandle_t Task_mkII_s1_Handle;

bool debounce_s1(void);

void task_mkII_s1(void *pvParameters);

#endif /* TASK_MKII_S1_H_ */
