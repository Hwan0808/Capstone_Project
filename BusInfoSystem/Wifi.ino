#include <ESP8266WiFi.h> // ESP 8266 와이파이 라이브러리

// 와이파이 연결 하기
boolean connect_ap(char* ssid, char* password) {
  
  int count = 30; // 최대 30 회 연결 시도 중 wifi 연결하면 성공, 아니면 실패
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

  server.on("/", handleRoot); // 루트에 접속 되었을때 실행할 함수

  server.begin(); // 웹서버 시작
  Serial.println("HTTP server started"); 
  
  Serial.write(Serial.read());
  return(true);
}

void handleRoot() { // 루트에 접속할때 실행할 내용
  server.send(200, "text/plain", "hello ~!~!~!");
}
