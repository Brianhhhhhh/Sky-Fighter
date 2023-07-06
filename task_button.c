//author: Brian Huang


#include <main.h>

 QueueHandle_t Queue_BUTTON;
 extern int enemy_array_width;
 extern int enemies[][3];
 extern int bullet_array_width;
 extern int bullets[][3];
 extern int x;
 extern int y;

/******************************************************************************
* Add enemy whenever there is an empty space
******************************************************************************/
static void add_enemy(void)
{
    int i;
    for(i = 0; i < 6; i++){
        enemies[enemy_array_width][0] = 11 + 20 * i;
        enemies[enemy_array_width][1] = 10;
        enemies[enemy_array_width][2] = 1;
        enemy_array_width++;
    }
}

/******************************************************************************
* Shoot out the bullet from the aircraft
******************************************************************************/
static void bullet_shot(void)
{
    bullets[bullet_array_width][0] = x;
    bullets[bullet_array_width][1] = y - 8;
    bullets[bullet_array_width][2] = 1;
    bullet_array_width++;
}

/******************************************************************************
* Controls the Buttons on the MKII BoosterPack
******************************************************************************/
void Task_BUTTON(void *pvParameters)
{
    BUTTON_MSG_t msg;

    while(1)
    {
        /* Wait until we receive a message from the Queue_BUTTON
         */
        xQueueReceive(Queue_BUTTON, &msg, portMAX_DELAY);

       /* take Sem_UART semaphore
        */
        xSemaphoreTake(Sem_UART,portMAX_DELAY);

        printf("Task_BUTTON received button_pressed message\n\r");

        /* give Sem_UART semaphore
         */
        xSemaphoreGive(Sem_UART);


        /* Design the specific function based on the message
         * received from BUTTON_LED.
         *
         * The button type is also specified
         * in the message received from Queue_LED.
         *
         */
        if(msg.button == S1){
            //add enemy
            add_enemy();
        }else{
            //shoot the bullet
            bullet_shot();
        }
    }

}



