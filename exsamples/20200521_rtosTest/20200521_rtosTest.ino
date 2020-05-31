/*
 *  Copyright(C) 2018 by Yukiya Ishioka
 */

#include <freertos/FreeRTOS.h>    /* FreeRTOSを用いるためのヘッダファイル */

#define  LED1PIN   22    /* LED1のポート番号 */
#define  LED2PIN   23    /* LED2のポート番号 */

void  task1( void *param )
{
  int i = 0;
  while( 1 ) {
    i=i+1;
    vTaskDelay(500);
    Serial.print("task1 : ");
    Serial.print(i,DEC);
    Serial.println();

  }
}

void  task2( void *param )
{
  int j = 0;
  while( 1 ) {
    j=j+1;
    vTaskDelay(200);
    Serial.print("task2 : ");
    Serial.print(j,DEC);
    Serial.println();
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.print("setup()\n");

  pinMode(LED1PIN, OUTPUT);
  pinMode(LED2PIN, OUTPUT);
  digitalWrite(LED1PIN, LOW);  /* LED1 off */
  digitalWrite(LED2PIN, LOW);  /* LED2 off */

  /* create task */
  xTaskCreatePinnedToCore( task1,   /* タスクの入口となる関数名 */
                           "TASK1", /* タスクの名称 */
                           8192,   /* スタックサイズ */
                           NULL,    /* パラメータのポインタ */
                           1,       /* プライオリティ */
                           NULL,    /* ハンドル構造体のポインタ */
                           0 );     /* 割り当てるコア (0/1) */

  xTaskCreatePinnedToCore( task2,
                           "TASK2",
                           8192,
                           NULL,
                           2,
                           NULL,
                           0 );
}

void loop()
{
  Serial.print("loop()\n");
  vTaskDelay(1000);
}
