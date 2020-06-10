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

  setupTFTScreen();

  //pinMode(LED1PIN, OUTPUT);
  //pinMode(LED2PIN, OUTPUT);
  //digitalWrite(LED1PIN, LOW);  /* LED1 off */
  //digitalWrite(LED2PIN, LOW);  /* LED2 off */

  /* create task */
  xTaskCreatePinnedToCore( task1,   /* タスクの入口となる関数名 */
                           "TASK1", /* タスクの名称 */
                           4096,   /* スタックサイズ */
                           NULL,    /* パラメータのポインタ */
                           1,       /* プライオリティ */
                           NULL,    /* ハンドル構造体のポインタ */
                           0 );     /* 割り当てるコア (0/1) */

  xTaskCreatePinnedToCore( task2,
                           "TASK2",
                           4096,
                           NULL,
                           2,
                           NULL,
                           0 );

  xTaskCreatePinnedToCore( task_SC16IS740_TEST,
                           "TASK_SC16IS740_TEST",
                           4096,
                           NULL,
                           3,
                           NULL,
                           0 );

  xTaskCreatePinnedToCore( task_SDTest,
                           "TASK_SDTest",
                           4096,
                           NULL,
                           4,
                           NULL,
                           0 );
                           
  xTaskCreatePinnedToCore( task_TFTScreen,
                           "TASK_SDTest",
                           4096,
                           NULL,
                           5,
                           NULL,
                           0 );                           
}

void loop()
{
  Serial.print("loop()\n");
  vTaskDelay(1000);
}
