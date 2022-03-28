#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

#define _SSID "KT_GiGA_AAE1"        // Your WiFi SSID
#define _PASSWORD "edcd6eg366"    // Your WiFi Password
#define PROJECT_ID "capstone-project-31a2c-default-rtdb.firebaseio.com/"   // Your Firebase Project ID. Can be found in project settings.

//Firebase firebase(PROJECT_ID);    // SLOW BUT HASTLE-FREE METHOD FOR LONG TERM USAGE. DOES NOT REQUIRE PERIODIC UPDATE OF FINGERPRINT

// 와이파이 연결 하기
boolean connect_ap(char* ssid, char* password) {
  int count = 30;                                 // 최대 30 회 연결 시도 중 wifi 연결하면 성공, 아니면 실패
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    wifi_oled(count);
    if (!count--) {
      Serial.print("\nNO WIFI");
      return(false);
    }
  }
  previousMillis = millis();
  Serial.print("\nGot WiFi, IP address: ");
  Serial.println(WiFi.localIP()); 
  Serial.write(Serial.read());
  return(true);
}
