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
#pragma once

// 
// Hardware Settings
//
#define APP_NAME              "WifiStatusDisplay8266"
#define APP_VERSION_MAJOR     1
#define APP_VERSION_MINOR     0
#define APP_VERSION_PATCH     0

#define PIN_BOARD_LED         D0  // blue LED on NodeMCU
#define PIN_RS                D6  // Display R/S
#define PIN_EN                D5  // Display Enable
#define PIN_D4                D4  // Display D4
#define PIN_D5                D3  // Display D5
#define PIN_D6                D2  // Display D6
#define PIN_D7                D1  // Display D7

#define DISPLAY_NUM_COL       16
#define DISPLAY_NUM_ROW       2


//
// Configuration Settings
//
//#define CONFIG_DEBUG_NOTFOUND   // uncomment to return debug info when url not found.
//#define CONFIG_ENABLE_OTA       // uncomment to enable firmware update over the air (OTA)

// Specify the URL of the server which serves the display content here:
#define CONFIG_URL "http://server:port/aaa/bbb"
// Server needs to respond with json in the following format:
// { 
//   "content": [
//     "row0 text",
//     "row1 text"
//     ...
//     ]
//   "interval": 10000,                 
//   "sessionId": 0,                     
//   "url": "http://xxx.yyy/aaa/bbb"    
// }
//
// "content"   - Array of strings with the content for each row of the display.
// "interval"  - Optional. Element which describes the delay in milliseconds for the next query.
// "sessionId" - Optional. A session id which will be appended as argument to the url 
// "url"       - Optional. The url for the next query. Replaces CONFIG_URL.



// 
// Network Settings
//
#define CONFIG_WIFI_SSID      "xxx"
#define CONFIG_WIFI_PASSWORD  "yyy"

