/*
The MIT License (MIT)

Copyright (c) 2018 sebakrau

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <LiquidCrystal.h>    // LCD
#include <WiFiUdp.h>          // OTA
#include <ArduinoOTA.h>       // OTA
#include <ArduinoJson.h>
#include "config.h"


//
// Macros
//
#define STRINGIFY_(x) #x
#define STRINGIFY(s)  STRINGIFY_(s)


//
// Globals
//
ESP8266WebServer g_server(80);
LiquidCrystal g_lcd(PIN_RS, PIN_EN, PIN_D4, PIN_D5, PIN_D6, PIN_D7);


//
// LED
//
void LED_init() {
  pinMode(PIN_BOARD_LED, OUTPUT); 
}

void LED_board_set(bool enabled) {
  if (enabled) {
    digitalWrite(PIN_BOARD_LED, HIGH); 
  } else {
    digitalWrite(PIN_BOARD_LED, LOW); 
  }
}



//
// WiFi
//
void WIFI_enableOTA() {
  // Port defaults to 8266
  // ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
  // ArduinoOTA.setHostname("myesp8266");

  // No authentication by default
  // ArduinoOTA.setPassword((const char *)"123");

  ArduinoOTA.onStart([]() {
    Serial.println("OTA: Start");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("OTA Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
}

void WIFI_init() {
  Serial.print("Connecting to ");
  Serial.println(CONFIG_WIFI_SSID);

  WiFi.begin(CONFIG_WIFI_SSID, CONFIG_WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi connected, IP: ");
  Serial.println(WiFi.localIP());

#ifdef CONFIG_ENABLE_OTA
  Serial.println("OTA update is enabled!");
  WIFI_enableOTA();
#else  
  Serial.println("OTA update is disabled!");
#endif
}


//
// LCD
//
void LCD_init() {
  g_lcd.begin(DISPLAY_NUM_COL, DISPLAY_NUM_ROW);
}


//
// Setup
//
void setup() {
  // Init board
  LED_init();
  LED_board_set(true);
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.println();

  // Init display
  LCD_init();
  g_lcd.print("Connect WiFi...");
  
  // Connect WiFi 
  WIFI_init();

  // Go, go, go...
  Serial.println("READY");
  g_lcd.clear();
  g_lcd.print("Load data...");
}


//
// LOOP
//
void loop() {

  static long interval = 10000;
  static unsigned long previousMillis = 0 - interval; 
  unsigned long currentMillis = millis();

  // Query the server only in the given interval.
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    if (WiFi.status() == WL_CONNECTED) { 
  
      // Query for display content from the server.
      // We provide the size of the display as parameters to the server.
      HTTPClient http;  
      http.begin( CONFIG_URL "?numRow=" STRINGIFY(DISPLAY_NUM_ROW)  "&numCol="  STRINGIFY(DISPLAY_NUM_COL) );
      int httpCode = http.GET();                                
   
      if (httpCode == HTTP_CODE_OK) { 
        String payload = http.getString();  
        Serial.println(payload);   

        // Decode the packet.
        StaticJsonBuffer<200> jsonBuffer;
        JsonObject& root = jsonBuffer.parseObject(payload);

        if (root.success()) {

          // Write content to display.
          g_lcd.clear();
          for (int i = 0; i < DISPLAY_NUM_ROW; i++) {
            g_lcd.setCursor(0, i);
            String content = root["content"][i];
            content.replace("°", "\xDF");   // map character code of HD44780 display chipset
            g_lcd.print(content);
          }

          // Update interval?
          if (root.containsKey("interval")) {
            interval = root["interval"];
          }
          
        } else {
          g_lcd.clear();
          g_lcd.print("parse error");
        }
                 
      } else {
        Serial.println("Error in HTTP request");
        g_lcd.clear();
        g_lcd.print("http error");
      }
            
      http.end();   
    } else {
      g_lcd.clear();
      g_lcd.print("lost connection");
    }
  }
 
  
  
#ifdef CONFIG_ENABLE_OTA
  ArduinoOTA.handle();
#endif
}




