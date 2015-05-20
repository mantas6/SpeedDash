# SpeedDash
Bicycle speedometer project powered by Arduino.

I'm using Arduino Pro Mini 3.3V with 128x64 OLED SPI screen.

Also using two graphics libraries:
<br><a href="https://github.com/adafruit/Adafruit-GFX-Library">Adafruit_GFX</a>
<br><a href="https://github.com/adafruit/Adafruit_SSD1306">Adafruit_SSD1306</a>

Unit has two speed sensors one for cadence and other for speed.

A3144 hall effect sensors are used and connected to the interrupt pins (2 and 3). (8K pull-ups are used for each)

On the display you can see: speed, cadence (value and graph), and odometer.
<img src="http://i.imgur.com/zrawZOI.jpg">
