//author: Brian Huang


#ifndef MAIN_H_
#define MAIN_H_

#include "msp.h"
#include "msp432p401r.h"
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

/* RTOS header files */
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <task_button.h>
#include <task_mkII_s1.h>
#include <task_mkII_s2.h>
#include <task_accelerometer.h>
#include <ece353.h>
#include "game.h"
#include "lcd.h"
#include "game_images.h"
#include <stdlib.h>
#include "i2c.h"
#include "opt3001.h"
#include"timer32.h"
#include "music.h"

extern SemaphoreHandle_t Sem_UART;


#endif /* MAIN_H_ */
