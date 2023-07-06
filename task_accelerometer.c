//author: Brian Huang


#include <main.h>


 TaskHandle_t Task_Accelerometer_Handle;
 TaskHandle_t Task_Accelerometer_Timer_Handle;

 volatile uint32_t ACC_X_DIR = 0;
 volatile uint32_t ACC_Y_DIR = 0;

 /********************************
 * Initialization of Accelerometer
 ********************************/
  void Task_Accelerometer_Init(void)
  {
      // Configure X direction.
      P6->SEL0 |= BIT1;
      P6->SEL1 |= BIT1;

      // Configure Y direction.
      P4->SEL0 |= BIT0;
      P4->SEL1 |= BIT0;

      //ADC14 set-up
      ADC14->CTL0 = ADC14_CTL0_SHT0_2 | ADC14_CTL0_SHP | ADC14_CTL0_CONSEQ_1;
      ADC14->CTL1 = ADC14_CTL1_RES_2;

      //Map X,Y direction signal to the corresponding MCTL, and Y direction as the end of sequence
      ADC14->MCTL[0] |= ADC14_MCTLN_INCH_14;
      ADC14->MCTL[1] |= ADC14_MCTLN_INCH_13 | ADC14_MCTLN_EOS;

      // Enable ADC Interrupt
      ADC14->IER0 |=  ADC14_IER0_IE1;
      NVIC_EnableIRQ(ADC14_IRQn);
      NVIC_SetPriority(ADC14_IRQn,2);

      // Turn ADC ON
      ADC14->CTL0 |= ADC14_CTL0_ON;

  }

 /******************************************************************************
 * Used to start an ADC14 Conversion
 ******************************************************************************/
 void Task_Accelerometer_Timer(void *pvParameters)
 {
     while(1)
     {
         /*
          * Start the ADC conversion
          */
         ADC14->CTL0 |= ADC14_CTL0_SC | ADC14_CTL0_ENC;

         /*
          * Delay 50mS
          */
         vTaskDelay(pdMS_TO_TICKS(50));

     }
 }


/******************************************************************************
* Bottom Half Task.  Examines the ADC data from the ACC on the MKII
******************************************************************************/
void Task_Accelerometer_Bottom_Half(void *pvParameters)
{
    ACC_DIR_t dir;
    ACC_DIR_t prev_dir = ACC_DIR_CENTER;


    while(1)
    {
        /* Wait until we get a task notification from the ADC14 ISR
         */
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);



        /*
         * Set the dir variable to one of the following values based
         * on the values of ACC_X_DIR and ACC_Y_DIR
         */
        if(ACC_X_DIR < VOLT_0P85)
        {
           dir = ACC_DIR_LEFT;
        }
        else if(ACC_X_DIR > VOLT_2P50)
        {
            dir = ACC_DIR_RIGHT;
        }
        else if(ACC_Y_DIR < VOLT_0P85)
        {
            dir = ACC_DIR_DOWN;
        }
        else if(ACC_Y_DIR > VOLT_2P50)
        {
            dir = ACC_DIR_UP;
        }
        else
        {
            dir = ACC_DIR_CENTER;
        }

        /* ADD CODE
         * Send dir to Queue_Console if the the current direction
         * of the ACC does not match the previous direction of the ACC
         */
        if(dir != prev_dir){
            xQueueSendToBack(Queue_game_info, &dir, portMAX_DELAY);
        }


        /* ADD CODE
         * Update the prev_dir of the ACC
         */
        prev_dir = dir;
    }
}


/******************************************************************************
* Top Half of ADC14 Handler.
******************************************************************************/
void ADC14_IRQHandler(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    ACC_X_DIR = ADC14->MEM[0]; // Read the value and clear the interrupt
    ACC_Y_DIR = ADC14->MEM[1]; // Read the value and clear the interrupt


    /* Send a task notification to Task_ACC_Bottom_Half
     */
    vTaskNotifyGiveFromISR(Task_Accelerometer_Handle, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}



