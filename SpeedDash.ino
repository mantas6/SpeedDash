#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

//Wheel Circumference
#define WHEEL 2261

//Cadence
float rpm = 0;
long rpmtime = 0;

//Speed
float spd = 0;
long spdtime = 0;

//Stats
long stattime = 0;
float odo = 0;

void setup()   {                
  Serial.begin(9600);
  
  display.begin(SSD1306_SWITCHCAPVCC);
  
  /* Attaching interrupt functions */
  attachInterrupt(0, spdInt, RISING);
  attachInterrupt(1, rpmInt, RISING);
}

void rpmInt()
{ 
  int time = millis() - rpmtime;
  rpmtime = millis();
  
  rpm = (1 / (float(time) / 1000)) * 60;
}

void spdInt()
{
  int time = millis() - spdtime;
  spdtime = millis();
  
  spd = ((1 / (float(time) / 1000)) * 60) * WHEEL / 10 / 100 / 1000 * 60; 
}

void stat()
{
  if(stattime + 1000 < millis())
  {
    int time = millis() - stattime;

    stattime = millis();

    odo += spd / 60 / 60 / 1000 * time;
  }

  /* Resets values if there is not movement */
  if(millis() - spdtime > 2000) spd = 0;
  if(millis() - rpmtime > 2000) rpm = 0;
}


void loop() {
  char temp[10];
  
  display.clearDisplay();

  /* Converting RPM to graph value */
  int rpmg = rpm * 2 - 80;
  
  /* Cadence Bar */
  for(int a = 0; a < rpmg; a++)
  {
    if(a > 250 || a < 0) break;
    
    if(a < 65)
    {
      display.drawLine(0, 64 - a, 4, 64 - a, WHITE);
    }
    else if(a < 188)
    {
      display.drawLine(a - 60, 0, a - 60, 4, WHITE);
    }
    else
    {
      display.drawLine(123, a - 184, 128, a - 184, WHITE);
    }
  }
  
  /* Rectange for Cadence Bar */
  display.drawRect(6, 6, 116, display.height()-2*1, WHITE);
  
  /* Speed */
  display.setCursor(15,15);
  display.setTextColor(WHITE);
  display.setTextSize(4);
  display.print(dtostrf((spd > 99 ? 99 : spd), 2, 0, temp));
  
  /* Speed Decimal Point */
  display.setCursor(64,15);
  display.setTextColor(WHITE, BLACK);
  display.setTextSize(2);
  display.print(int((abs(spd) - floor(spd)) * 10));
  
  /* Cadence */
  display.setCursor(64,35);
  display.setTextColor(WHITE, BLACK);
  display.setTextSize(1);
  display.print(dtostrf(rpm, 2, 0, temp));

  /* Odometer */
  display.setCursor(10,45);
  display.setTextColor(WHITE, BLACK);
  display.setTextSize(1);
  display.print(dtostrf(odo, 2, 2, temp));
  display.print("km");

  display.display();
  
  delay(100);
  stat();
}