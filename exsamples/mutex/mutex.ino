SemaphoreHandle_t xMutex = NULL;
 int sharedResource = 0;

 static void vTask1(void *pvParameters)
 {
     BaseType_t xStatus;
     const TickType_t xTicksToWait = 1000UL; //
     xSemaphoreGive(xMutex);

     while(1)
     {
         xStatus = xSemaphoreTake(xMutex, xTicksToWait);

         Serial.println("check for mutex (task1)");

         if(xStatus == pdTRUE)
         {
             sharedResource = 100;
             Serial.print("shared resource change by task1 : ");
             Serial.println(sharedResource);
         }

         xSemaphoreGive(xMutex);
         delay(500);
     }
 }

 static void vTask2(void *pvParameters)
 {
     BaseType_t xStatus;
     const TickType_t xTicksToWait = 500UL;
     xSemaphoreGive(xMutex);

     while(1)
     {
         xStatus = xSemaphoreTake(xMutex, xTicksToWait);

         Serial.println("check for mutex (task2)");

         if(xStatus == pdTRUE )
         {
             sharedResource = 1;
             Serial.print("shared resource change by task2 : ");
             Serial.println(sharedResource);
         }

         xSemaphoreGive(xMutex);
         delay(1000);
     }
 }

 void setup()
 {
     Serial.begin(115200);

     xMutex = xSemaphoreCreateMutex();

     if( xMutex != NULL )
     {
         // higher priority task is done before lower priority task
         // if there are some same priority tasks, they are kicked in order of registration
         xTaskCreate(vTask1, "Task1", configMINIMAL_STACK_SIZE, NULL, 1,(TaskHandle_t *) NULL);
         xTaskCreate(vTask2, "Task2", configMINIMAL_STACK_SIZE, NULL, 2,(TaskHandle_t *) NULL);
     }
     else {
         while(1)
         {
             Serial.println("rtos mutex create error, stopped");
             delay(1000);
         }
     }
 }

 void loop()
 {
 }
