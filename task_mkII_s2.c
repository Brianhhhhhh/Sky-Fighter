//author: Brian Huang


#include "task_mkII_s2.h"

TaskHandle_t Task_mkII_s2_Handle = NULL;



/******************************************************************************
 * De-bounce switch S2.
 *****************************************************************************/
bool debounce_s2(void)
{
    static uint8_t debounce_state = 0x00;

    // Shift the de-bounce variable to the left
    debounce_state = debounce_state << 1;

    // If S1 is being pressed, set the LSBit of debounce_state to a 1;
    if(ece353_MKII_S2())
    {
        debounce_state |= 0x01;
    }

    // If the de-bounce variable is equal to 0x7F, set debounce of s2 to true.
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
 * De-bounce switch S2.  If is has been pressed, shoot the bullet from the aircraft.
 *****************************************************************************/
void task_mkII_s2(void *pvParameters)
{
    BUTTON_MSG_t msg;


    while(1)
    {
        if(debounce_s2())
        {

            /* ADD CODE
             * Take Sem_UART
             */
            xSemaphoreTake(Sem_UART,portMAX_DELAY);
            printf("Button S2 has been pressed\n\r");

            /* ADD CODE
             * Give Sem_UART
             */
            xSemaphoreGive(Sem_UART);

            msg.button = S2;


            /* ADD CODE
             * Send msg to Queue_BUTTON
             */
            xQueueSendToBack(Queue_BUTTON, &msg, portMAX_DELAY);
        }

        // Delay for 10mS using vTaskDelay
        vTaskDelay(pdMS_TO_TICKS(10));
    }

}
