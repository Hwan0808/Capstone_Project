#include "SSD1306.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Arduino.h>

SSD1306 display(0x3c, D3, D4);

unsigned long startTime = 0;
uint32_t loopcnt = 0;
char fpsbuf[128] = "FPS:";
bool invert = true;  // 화면을 역상으로 표시

void setup_oled(){
  display.init();
  display.clear();  
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  display.display();
}

void wifi_oled(int cnt) {
  display.clear();  
  display.setFont(ArialMT_Plain_10);
  display.drawString(0,0, "Waiting WIFI..."); 
  display.drawString(0,13, String("SSID : ")+String(ssid));
  display.drawString(0,26, String("PW : ")+ String(password)); 
  display.drawString(0,39, String(cnt));
  display.display();  
}

void nowifi_oled() {
  display.clear();  
  display.setFont(ArialMT_Plain_10);
  display.drawString(0,0, "NO WIFI: Skip WIFI..."); 
  display.display();  
}

String getTime(unsigned long  ttime) {
  int sec = ttime / 1000; int min = sec / 60; int hr = min / 60;
  String ts = "";
  if (hr < 10) ts += "0";
  ts += hr;   ts += ":";
  if ((min % 60) < 10) ts += "0";
  ts += min % 60;   ts += ":";
  if ((sec % 60) < 10) ts += "0";
  ts += sec % 60;
  return (ts);
}

void do_oled(int16_t x, int16_t y, String result) {
  
  startTime = millis();
  unsigned long  ttime = millis();
  dtostrf(loopcnt * 1000.0 / (ttime - startTime), 5, 2,   fpsbuf + 4);
  
  display.clear(); 
  display.setFont(ArialMT_Plain_10);
  display.drawString(15,0, "Sosa Station(11360)");
  display.setFont(ArialMT_Plain_10);
  display.drawString(15,13, result_95);
  display.drawString(15,26, result_56);
  display.drawString(15,39, result_60);
  display.drawString(15,52, getTime(ttime));
  display.display();
  Serial.println(result);

  loopcnt++;
}
