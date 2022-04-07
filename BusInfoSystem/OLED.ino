#include "SSD1306.h"
#include <ESP8266WiFi.h>
#include "SPI.h"
#include <SPI.h>
#include <Wire.h>
#include <ArduinoJson.h>
#include <Arduino.h>

SSD1306 display(0x3c, D3, D4);

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

void do_oled(int16_t x, int16_t y, String result) {
  display.clear(); 
  display.setFont(ArialMT_Plain_10);
  display.drawString(15,0, "Sosa Station(11360)");
  display.setFont(ArialMT_Plain_10);
  display.drawString(22,13, result_95);
  display.drawString(22,26, result_56);
  display.drawString(22,39, result_60);
  display.drawString(10,52, Weather);
  display.display();
  Serial.println(result);
}
