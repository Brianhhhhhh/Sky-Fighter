//author: Brian Huang

#include "main.h"

SemaphoreHandle_t Sem_UART;

/*
 *  ======== main ========
 */
int main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    //Initialization of different tasks and interrupts
    Task_Accelerometer_Init();
    ece353_MKII_S1_Init();
    ece353_MKII_S2_Init();
    i2c_init();
    opt3001_init();
    Crystalfontz128x128_Init();
    T32_INI2();
    __enable_irq();

    Sem_UART =  xSemaphoreCreateBinary();

    /*  Initialize Queue_BUTTON so that it is of size 2, and each entry
     *  is a BUTTON_MSG_t.
     */
    Queue_BUTTON = xQueueCreate(10,sizeof(BUTTON_MSG_t));
    Queue_game_info = xQueueCreate(10,sizeof(ACC_DIR_t));

    // Release print semaphore.
    xSemaphoreGive(Sem_UART);


    xTaskCreate
    (   task_game_play,
        "Task_game_play",
        configMINIMAL_STACK_SIZE,
        NULL,
        1,
        &Task_game_play_Handle
    );

    xTaskCreate
    (   task_mkII_s1,
        "task_mkII_s1",
        configMINIMAL_STACK_SIZE,
        NULL,
        1,
        NULL
    );

    xTaskCreate
     (   task_mkII_s2,
         "task_mkII_s2",
         configMINIMAL_STACK_SIZE,
         NULL,
         1,
         NULL
     );

    xTaskCreate
    (   Task_BUTTON,
        "Task_BUTTON",
        configMINIMAL_STACK_SIZE,
        NULL,
        1,
        NULL
    );

    xTaskCreate
    (   Task_Accelerometer_Timer,
        "Task_Accelerometer_Timer",
        configMINIMAL_STACK_SIZE,
        NULL,
        2,
        &Task_Accelerometer_Timer_Handle
    );

    xTaskCreate
    (   Task_Accelerometer_Bottom_Half,
        "Task_Accelerometer",
        configMINIMAL_STACK_SIZE,
        NULL,
        3,
        &Task_Accelerometer_Handle
    );


    /* Start the FreeRTOS scheduler */
    vTaskStartScheduler();

    while(1){};

}

//*****************************************************************************
//
//! \brief Application defined malloc failed hook
//!
//! \param  none
//!
//! \return none
//!
//*****************************************************************************
void vApplicationMallocFailedHook()
{
    /* Handle Memory Allocation Errors */
    while(1)
    {
    }
}

//*****************************************************************************
//
//! \brief Application defined stack overflow hook
//!
//! \param  none
//!
//! \return none
//!
//*****************************************************************************
void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
{
    //Handle FreeRTOS Stack Overflow
    while(1)
    {
    }
}
