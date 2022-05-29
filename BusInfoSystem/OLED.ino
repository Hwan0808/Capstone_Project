#include "SSD1306.h"
#include <ESP8266WiFi.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <Wire.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET LED_BUILTIN // Reset pin #
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int frame_delay = 60;

void setup_oled(){
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);
  display.clearDisplay();
}

void wifi_oled() 
{
  for( int i = 0; i < IMAGE_COUNT; i++)
  {
    display.clearDisplay();
    display.drawBitmap((SCREEN_WIDTH-IMAGE_WIDTH)/2, 0, frame[i], IMAGE_WIDTH, IMAGE_HEIGHT, 2);
    display.display();  
    delay(frame_delay);
  }
}

void Got_wifi() {
  display.clearDisplay();
  display.setTextColor(WHITE);   
  display.setTextSize(2);
  display.setCursor(42,15);
  display.println("WIFI");
  display.setCursor(10,35);
  display.println("CONNECTED");
  display.display();
}

void nowifi_oled() {
  display.clearDisplay();
  display.setTextColor(WHITE);   
  display.setTextSize(2);
  display.setCursor(42,15);
  display.println("WIFI");
  display.setCursor(10,35);
  display.println("DISCONNECTED");
  display.display();  
}

void do_oled1(String result) {
  display.clearDisplay(); 
  display.setTextColor(WHITE); 
  display.setTextSize(1);
  display.setCursor(10,0);
  display.println("Sosa Station(11360)");
  display.println();
  display.println(result_95);
  display.println(result_56);
  display.println(result_60);
  display.println("---------------------");
  display.setCursor(5,47);
  display.println(Weather);
  display.display();
  Serial.println(result);
}

void do_oled2(String result) {
  display.clearDisplay();
  display.setTextColor(WHITE);  
  display.setTextSize(1);
  display.setCursor(10,0);
  display.println("KNUT Station(27011)");
  display.println();
  display.println(result_1_2);
  display.println(result_1_5);
  display.println(result_5);
  display.println("---------------------");
  display.setCursor(5,47);
  display.println(Weather);
  display.display();
  Serial.println(result);
}

void do_oled3(String result) {
  display.clearDisplay();
  display.setTextColor(WHITE); 
  display.setTextSize(1);
  display.setCursor(10,0);
  display.println("Janghyeon 4 (59031)");
  display.println();
  display.println(result_3300);
  display.println(result_3301);
  display.println(result_530);
  display.println("---------------------");
  display.setCursor(5,47);
  display.println(Weather);
  display.display();
  Serial.println(result);
}
