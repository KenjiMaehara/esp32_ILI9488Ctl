
void  task2( void *param )
{
  int j = 0;
  while( 1 ) {
    j=j+1;
    vTaskDelay(3000);
    Serial.print("task2 : ");
    Serial.print(j,DEC);
    Serial.println();
  }
}
