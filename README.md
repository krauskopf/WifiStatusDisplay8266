# WiFi Status LCD

A very simple wifi-based status display, which queries its content from an http server. For example, it can be 
used together with Node-RED as a low-cost visualization.
An ESP8266 ESP-12E NodeMcu WiFi board is used for connectivity


## Usage
After boot, the controller continuously queries a given server url.
The server needs to respond with a json object in the following format:
	
	{ 
	  "content": [
		"row0 text",
		"row1 text"
		...
		]
	  "interval": 10000,
	}
	
Description:
 * ´content´: Array of strings with the content for each row of the display.
 * ´interval´: Optional element which describes the delay in milliseconds for the next query.
 
The contents will be written to the display and the server will be queried again in the next interval.
 

## Build instructions

### Firmware
To build the arduino sketch:

- Install Arduino IDE
  - Use the Arduino Board Manager to install the ESP8266 toolchain (https://github.com/esp8266/Arduino) 
  - Use the Arduino Library Manager to install ArduinoJSON (https://bblanchon.github.io/ArduinoJson/)
- Open the sketch and modify the settings in the `config.h` header. You have to set the SSID and password of your wifi network.
- Compile and download to nodemcu.
 

## History
- 2018-jan-28: 1.0.0 - Created first version.


## Credits
- Sebastian Krauskopf (sebakrau)

## License
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
