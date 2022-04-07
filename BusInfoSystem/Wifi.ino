#include <ESP8266WiFi.h> // ESP 8266 와이파이 라이브러리

boolean connect_ap(char* ssid, char* password) { // 와이파이 연결 하기
  
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

  server.on("/", handleRoot); // 루트에 접속 되었을때 실행할 함수 (웹서버 동작시에 실행하는 함수)
  server.begin(); // 웹서버 시작

  Serial.println("HTTP server started"); 
  
  Serial.write(Serial.read());
  return(true);
}


void handleRoot() { // 루트에 접속할때 실행할 내용 (웹서버 동작시에 실행하는 코드)

  String webpage = "<!DOCTYPE html><html><head><meta http-equiv=\"refresh\" content=\"5\"><title>BUSKER BUSKER 1.0</title><style>";
  webpage += "a:link {background-color: YELLOW; text-decoration: none;}";
  webpage += "table, th, td {border: 1px solid black;} </style> </head> <body> <h1  style=";
  webpage += "font-size:300%;";
  webpage += " ALIGN=CENTER>BUSKER BUSKER 1.0</h1>";
  webpage += "<p ALIGN=CENTER style=""font-size:150%;""";
  webpage += "> <b>Location Details</b></p> <table ALIGN=CENTER style=";
  webpage += "width:50%";
  webpage += ">";
  webpage += "<tr><th>BUS 95</th> <td ALIGN=CENTER >";
  webpage += result_95;
  webpage += "</td></tr><tr><th>BUS 56</th> <td ALIGN=CENTER >";
  webpage += result_56;
  webpage += "</td></tr><tr><th>BUS 60</th> <td ALIGN=CENTER >";
  webpage += result_60;
  webpage += "</td></tr><tr><th>Weather</th> <td ALIGN=CENTER >";
  webpage += Weather;
  webpage += "</td></tr></table> ";
  webpage += "<p ALIGN=CENTER><a href=\"http://www.gbis.go.kr/gbis2014/schBus.action?mapTabCd=3\">Location BUS 95</a>";
  webpage += "<a href=\"http://www.gbis.go.kr/gbis2014/schBus.action?mapTabCd=3\">Location BUS 56</a>";
  webpage += "<a href=\"http://www.gbis.go.kr/gbis2014/schBus.action?mapTabCd=3\">Location BUS 60</a></p>";
  webpage += "<p ALIGN=CENTER> Created By buskerbusker </p>";
  webpage += "<p ALIGN=CENTER> Copyright https://github.com/Hwan0808 All rights reserved.</p>";
  webpage += "</body></html> \n";

  server.send(200,"text/html",webpage);
  delay(100);

}
