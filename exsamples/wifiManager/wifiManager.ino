//#include <WiFi.h>
//#include <DNSServer.h>
//#include <WebServer.h>
//#include <WiFiManager.h>

#if defined(ESP8266)
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#else
#include <WiFi.h>          //https://github.com/esp8266/Arduino
#endif

//needed for library
#include <DNSServer.h>
#if defined(ESP8266)
#include <ESP8266WebServer.h>
#else
#include <WebServer.h>
#endif
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager


#define LED       2
#define INTERVAL  1000

char data;
unsigned long int timer;

WiFiManager wifiManager;

void setup()
{
  Serial.begin(115200);
  pinMode(LED,OUTPUT);

  wifiManager.setAPCallback(configModeCallback);
  wifiManager.setTimeout(60);
  if(!wifiManager.autoConnect("ESP32"))
  {
    Serial.println("failed to connect and hit timeout");
  }
  else
  {
    Serial.println("Successfully connected");
  }
  
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());    
}

void loop()
{
  if(millis()-timer>=INTERVAL)
  {
    timer=millis();
    digitalWrite(LED,!digitalRead(LED));
    if(digitalRead(LED)==LOW) Serial.println("LED OFF");
    else Serial.println("LED ON");
  } 

  if(Serial.available())
  {
    data=Serial.read();
    if(data=='1')
    {
      WiFi.disconnect(false,true);
      delay(3000);
      Serial.println("Reset wifi setting and restart");
      wifiManager.resetSettings();
      ESP.restart();      
    }
  }
}

void configModeCallback (WiFiManager *myWiFiManager)
{
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  Serial.println(myWiFiManager->getConfigPortalSSID());
}
