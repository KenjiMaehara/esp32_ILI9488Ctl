#include <WiFi.h>          //https://github.com/esp8266/Arduino
#include <WebServer.h>
#include <DNSServer.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager

// Include the correct display library
// For a connection via I2C using Wire include
#include "SSD1306.h" // alias for `#include "SSD1306Wire.h"`

// Include Unopuino32 pin definition
#include "Unopuino32.h"

// Initialize the OLED display using Wire library
SSD1306  display(0x3c, GPSDA, GPSCL);

void setup() {
    display.init();
    display.clear();

    display.flipScreenVertically();
    display.setFont(ArialMT_Plain_10);
    display.setTextAlignment(TEXT_ALIGN_LEFT);

    // put your setup code here, to run once:
    Serial.begin(115200);
    Serial.println("\n Starting");

    // is configuration portal requested?
    //WiFiManager
    //Local intialization. Once its business is done, there is no need to keep it around
    WiFiManager wifiManager;

    //reset settings - for testing
    //wifiManager.resetSettings();

    //sets timeout until configuration portal gets turned off
    //useful to make it all retry or go to sleep
    //in seconds
    //wifiManager.setTimeout(120);

    //it starts an access point with the specified name
    //here  "AutoConnectAP"
    //and goes into a blocking loop awaiting configuration

    //WITHOUT THIS THE AP DOES NOT SEEM TO WORK PROPERLY WITH SDK 1.5 , update to at least 1.5.1
    //WiFi.mode(WIFI_STA);

    display.drawString(0, 0, "AP mode: OnDemandAP");
    display.drawString(0, 10, "IP adrs: 192.168.4.1");
    display.display();

    if (!wifiManager.startConfigPortal("OnDemandAP")) {
      Serial.println("failed to connect and hit timeout");
      delay(3000);
      //reset and try again, or maybe put it to deep sleep
      ESP.restart();
      delay(5000);
    }

    //if you get here you have connected to the WiFi
    IPAddress ipadr = WiFi.localIP();

    Serial.println("connected(^^)");
    Serial.println("local ip");
    Serial.println(ipadr);
    Serial.println(WiFi.SSID());
    display.clear();
    display.drawString(0, 0, "connected (^^)");
    display.drawString(0, 10, "SSID: " + WiFi.SSID());
    display.drawString(0, 20, "IP adrs: " + (String)ipadr[0] + "." + (String)ipadr[1] + "." + (String)ipadr[2] + "." + (String)ipadr[3]);
    display.display();
}

void loop() {
  // put your main code here, to run repeatedly:
}
