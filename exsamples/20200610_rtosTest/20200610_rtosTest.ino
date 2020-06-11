/*
 *  Copyright(C) 2018 by Yukiya Ishioka
 */

#include <freertos/FreeRTOS.h>    /* FreeRTOSを用いるためのヘッダファイル */

//#define  LED1PIN   22    /* LED1のポート番号 */
//#define  LED2PIN   23    /* LED2のポート番号 */




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

  #if 0
  xTaskCreatePinnedToCore( task_SDTest,
                           "TASK_SDTest",
                           4096,
                           NULL,
                           4,
                           NULL,
                           0 );
  #endif

  #if 1
  xTaskCreatePinnedToCore( task_TFTScreen,
                           "TASK_TFTScreen",
                           4096,
                           NULL,
                           5,
                           NULL,
                           0 );                           

  #endif
}

void loop()
{
  Serial.print("loop()\n");
  vTaskDelay(1000);
}
