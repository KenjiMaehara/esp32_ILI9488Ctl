/*
*  Copyright(C) 2018 by Yukiya Ishioka
*/

#include <freertos/FreeRTOS.h>    /* FreeRTOSを用いるためのヘッダファイル */

//#define  LED1PIN   22    /* LED1のポート番号 */
//#define  LED2PIN   23    /* LED2のポート番号 */

SemaphoreHandle_t xMutex = NULL;
int sharedResource = 0;


void setup()
{
  Serial.begin(115200);
  Serial.print("setup()\n");


  //pinMode(LED1PIN, OUTPUT);
  //pinMode(LED2PIN, OUTPUT);
  //digitalWrite(LED1PIN, LOW);  /* LED1 off */
  //digitalWrite(LED2PIN, LOW);  /* LED2 off */


  setupTFTScreen();
  /* create task */

  xMutex = xSemaphoreCreateMutex();

  if( xMutex != NULL )
  {

    #if 1
    xTaskCreate( task_SDTest,
      "TASK_SDTest",
      configMINIMAL_STACK_SIZE,
      NULL,
      1,
      (TaskHandle_t *) NULL);
      #endif

      #if 1
      xTaskCreate( task_TFTScreen,
        "TASK_TFTScreen",
        configMINIMAL_STACK_SIZE,
        NULL,
        2,
        (TaskHandle_t *) NULL);
        #endif
      }
      else
      {
        while(1)
        {
          Serial.println("rtos mutex create error, stopped");
          delay(1000);
        }
      }
    }

    void loop()
    {
      //Serial.print("loop()\n");
      //vTaskDelay(1000);
    }
