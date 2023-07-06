//author: Brian Huang


#include "task_mkII_s1.h"

TaskHandle_t Task_mkII_s1_Handle = NULL;


/******************************************************************************
 * De-bounce switch S1.
 *****************************************************************************/
bool debounce_s1(void)
{
    static uint8_t debounce_state = 0x00;

    // Shift the de-bounce variable to the left
    debounce_state = debounce_state << 1;

    // If S1 is being pressed, set the LSBit of debounce_state to a 1;
    if(ece353_MKII_S1())
    {
        debounce_state |= 0x01;
    }

    // If the de-bounce variable is equal to 0x7F, change the color of the tri-color LED.
    if(debounce_state == 0x7F)
    {
        return true;
    }
    else
    {
        return false;
    }

}

/******************************************************************************
 * De-bounce switch S1.  If is has been pressed, add the new enemy whenever the
 * space is available
 *****************************************************************************/
void task_mkII_s1(void *pvParameters)
{
    BUTTON_MSG_t msg;

    while(1)
    {

        if(debounce_s1())
        {

            /* Take Sem_UART
             */
            xSemaphoreTake(Sem_UART,portMAX_DELAY);

            printf("Button S1 has been pressed\n\r");

            /* Give Sem_UART
             */
            xSemaphoreGive(Sem_UART);

            msg.button = S1;


            /* Send msg to Queue_BUTTON
             */
            xQueueSendToBack(Queue_BUTTON, &msg, portMAX_DELAY);
        }

        // Delay for 10mS using vTaskDelay
        vTaskDelay(pdMS_TO_TICKS(10));
    }

}
