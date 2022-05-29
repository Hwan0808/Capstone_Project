#define serviceKey String ("A44txAbG4xvtwlhJfgd7SIHSndYpwkzy65BpHPG75%2Fdzqhqr%2FSlAjzYldYmYwhwLUPjsxB9PWh37iT10AwRCrg%3D%3D") // BusInfomation API Key

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
#include "location.h"
#include "image.h"
             
char* ssid = "KT_GiGA_AAE1"; // WIFI AP
char* password = "edcd6eg366"; // PassWord

// Google API key
String geolocationKey = "AIzaSyBqja_I-OFCSNvQq6BCWyayxl5-LgjkBJw";
String geocodingKey = "AIzaSyBqja_I-OFCSNvQq6BCWyayxl5-LgjkBJw";

int MCC = 450;  // Korea Country Code
int MNC = 8;    // Korea Network Code
String carrier = "KT Corp.";

Location myLocation;

const int GBISUPD_INTERVAL = 10000;
const int WEATHER_INTERVAL = 16000;
const char* host_1 = "apis.data.go.kr"; // BUS INFO URL
const char* host_2 = "www.kma.go.kr"; // WEATHER INFO URL

const int httpPort = 80; // Server Port (80)

WiFiClient client;

ESP8266WebServer server(80);  // WebServer Object Start

int cmdSize = 0;
String busstopID1 = "210000388"; // 소사역지하차도 버스정류장
String busstopID2 = "226000080"; // 한국교통대학교 버스정류장
String busstopID3 = "225000127"; // 장현4단지 버스정류장
String rcvbuf;
long currentMillis;
long previousMillis = 0;
boolean wifi_ready;
boolean requestLocker = false;
boolean requestLocker1 = false;
boolean requestLocker2 = true;
boolean requestLocker3 = true;
String result_95; String result_56; String result_60;
String result_1_2; String result_1_5; String result_5;
String result_3300; String result_3301; String result_530;

String Weather;

String LAT = "";
String LONG = "";

float LAT_value;
float LONG_value;

void setup() {
  Serial.begin(115200);
  setup_oled();
  logo_oled();
  wifi_ready = connect_ap(ssid, password); // 와이파이 연결 하기
  if (!wifi_ready){
    nowifi_oled();
  }
  // initialize the myLocation
  myLocation.begin(geolocationKey, geocodingKey, MCC, MNC, carrier);
  get_location();

  LAT_value = LAT.toFloat(); // 37.37
  LONG_value = LONG.toFloat(); // 126.80

  if ((LAT_value >= 37.47 && LAT_value <= 37.49) && (LONG_value >= 126.79 && LONG_value <= 126.81)) { 
      server.on("/", handleRoot1); // 접속 되었을때 실행할 함수 (웹서버 동작시에 실행하는 함수)
  }
  else if ((LAT_value >= 37.31 && LAT_value <= 37.33) && (LONG_value >= 126.93 && LONG_value <= 126.95)){
      server.on("/", handleRoot2); // 접속 되었을때 실행할 함수 (웹서버 동작시에 실행하는 함수)
  }
  else if ((LAT_value >= 37.36 && LAT_value <= 37.38) && (LONG_value >= 126.79 && LONG_value <= 126.81)){
      server.on("/", handleRoot3); // 접속 되었을때 실행할 함수 (웹서버 동작시에 실행하는 함수)
  }  
  server.begin(); // 웹서버 시작
  Serial.println("HTTP server started"); 
}
 
void loop(){
  while(client.available())
  {
    char c = client.read();
    if(c != NULL){
      if(rcvbuf.length() > 1300)
        rcvbuf = "";
      rcvbuf += c;
      //Serial.write(c);
      Serial.print(c);
    }
  }
  
  server.handleClient();

  if((LAT_value >= 37.47 && LAT_value <= 37.49) && (LONG_value >= 126.79 && LONG_value <= 126.81)) {
  
    if(millis() - previousMillis > GBISUPD_INTERVAL){ // 소사역
      result_95 = parseArrivalTime("95");
      do_oled1(result_95);
      do_oled1(result_56);
      do_oled1(result_60);
      do_oled1(Weather);
      requestLocker2 = true;
      requestLocker3 = true;
    }
 
    else if(millis() - previousMillis > GBISUPD_INTERVAL - 5000 && requestLocker)
    {
      result_56 = parseArrivalTime("56");
     
      // 95
      requestArrivalTime("212000005", "210000388");  
      requestLocker = false;
    }
   
    else if(millis() - previousMillis > GBISUPD_INTERVAL - 6000 && requestLocker1)
    {
      result_60 = parseArrivalTime("60");
 
      // 56
      requestArrivalTime("210000007", "210000388");  
      requestLocker1 = false;
      requestLocker = true;
    }
 
    else if(millis() - previousMillis > GBISUPD_INTERVAL - 7000 && requestLocker2)
    {
 
      // 60
      requestArrivalTime("210000043", "210000388");
      requestLocker2 = false;
      requestLocker1 = true;
    }
  
    else if(millis() - previousMillis > WEATHER_INTERVAL - 10000 && requestLocker3)
    {
    
      // 날씨 정보 받아오기
      requestWeatherApi();
      Weather = parseWeatherApi("Weather");
      requestLocker3 = false;
      requestLocker2 = true;
    }
} else if((LAT_value >= 37.31 && LAT_value <= 37.33) && (LONG_value >= 126.93 && LONG_value <= 126.95)) {
    
      if(millis() - previousMillis > GBISUPD_INTERVAL){ // 한국교통대학교 정류장
      result_1_2 = parseArrivalTime("1-2");
      do_oled2(result_1_2);
      do_oled2(result_1_5);
      do_oled2(result_5);
      do_oled2(Weather);
      requestLocker2 = true;
      requestLocker3 = true;
    }
 
    else if(millis() - previousMillis > GBISUPD_INTERVAL - 5000 && requestLocker)
    {
      result_1_5 = parseArrivalTime("1-5");
     
      // 1-2
      requestArrivalTime("208000021", "226000103");   
      requestLocker = false;
    }
   
    else if(millis() - previousMillis > GBISUPD_INTERVAL - 6000 && requestLocker1)
    {
      result_5 = parseArrivalTime("5");
 
      // 1-5
      requestArrivalTime("208000036", "226000103"); 
      requestLocker1 = false;
      requestLocker = true;
    }
 
    else if(millis() - previousMillis > GBISUPD_INTERVAL - 7000 && requestLocker2)
    {
 
      // 5
      requestArrivalTime("208000016", "226000103");
      requestLocker2 = false;
      requestLocker1 = true;
    }
  
    else if(millis() - previousMillis > WEATHER_INTERVAL - 10000 && requestLocker3)
    {
    
      // 날씨 정보 받아오기
      requestWeatherApi();
      Weather = parseWeatherApi("Weather");
      requestLocker3 = false;
      requestLocker2 = true;
    }
} else if((LAT_value >= 37.36 && LAT_value <= 37.38) && (LONG_value >= 126.79 && LONG_value <= 126.81)) {
    
      if(millis() - previousMillis > GBISUPD_INTERVAL){ // 시흥능곡역
      result_3300 = parseArrivalTime("3300");
      do_oled3(result_3300);
      do_oled3(result_3301);
      do_oled3(result_530);
      do_oled3(Weather);
      requestLocker2 = true;
      requestLocker3 = true;
    }
 
    else if(millis() - previousMillis > GBISUPD_INTERVAL - 5000 && requestLocker)
    {
      result_3301 = parseArrivalTime("3301");
     
      // 3300
      requestArrivalTime("224000047", "224001087");   
      requestLocker = false;
    }
   
    else if(millis() - previousMillis > GBISUPD_INTERVAL - 6000 && requestLocker1)
    {
      result_530 = parseArrivalTime("530");
 
      // 3301
      requestArrivalTime("224000057", "224001087"); 
      requestLocker1 = false;
      requestLocker = true;
    }
 
    else if(millis() - previousMillis > GBISUPD_INTERVAL - 7000 && requestLocker2)
    {
 
      // 530
      requestArrivalTime("224000029", "224001087");
      requestLocker2 = false;
      requestLocker1 = true;
    }
  
    else if(millis() - previousMillis > WEATHER_INTERVAL - 10000 && requestLocker3)
    {
    
      // 날씨 정보 받아오기
      requestWeatherApi();
      Weather = parseWeatherApi("Weather");
      requestLocker3 = false;
      requestLocker2 = true;
    }
  }
}

void requestArrivalTime(String routeId, String stationId) {
  String str = "GET /6410000/busarrivalservice/getBusArrivalItem?serviceKey=" + serviceKey + "&routeId=";
  str.concat(routeId);
  str.concat("&stationId=");
  str.concat(stationId);
  str.concat(" HTTP/1.1\r\nHost:apis.data.go.kr\r\nConnection: close\r\n\r\n");
  
  if(client.connect(host_1, httpPort)){
  Serial.println("connected");
  Serial.print(str);
  client.print(str);
  client.println();
 
  cmdSize = str.length();
 
  client.println("AT+CIPSTART=\"TCP\",\"apis.data.go.kr\",80");
  delay(500);
  client.print("AT+CIPSEND=");
  delay(500);
  client.println(cmdSize);
  delay(500);
  client.println(str);
  }
  else {
    Serial.println("Connection Failed: ");
    return;
  }
}
 
String parseArrivalTime(String busNum)
{
  previousMillis = millis();
  int startIndex = rcvbuf.indexOf("<predictTime1>");
  if(startIndex == -1){ 
    rcvbuf = "";
    return busNum + " : End of Service";
  }
 
  int strLength = strlen("<predictTime1>");
  int endIndex = rcvbuf.indexOf("<", startIndex + strLength);
  String predictTime1 = rcvbuf.substring(startIndex+strLength,endIndex);
  startIndex = rcvbuf.indexOf("<predictTime2>");
  strLength = strlen("<predictTime2>");
  endIndex = rcvbuf.indexOf("<", startIndex + strLength);
  String predictTime2 = rcvbuf.substring(startIndex+strLength,endIndex);
 
  if(predictTime2.equals("") && predictTime1 == "1"){
    return busNum + " : " + predictTime1 + "min";
  }
  else if(predictTime2.equals("") && predictTime1 != "1"){
  return busNum + " : " + predictTime1 + "mins";
  }
  
  Serial.println();
  Serial.println("===========");
  Serial.println(predictTime1);
  Serial.println(predictTime2);
  Serial.println("===========");
  rcvbuf = "";

  if (predictTime1 != "1" && predictTime2 != "1") { 
  return busNum + " : " + predictTime1 + "mins, " + predictTime2 + "mins";
  }
  else if (predictTime1 == "1" && predictTime2 != "1"){
  return busNum + " : " + predictTime1 + "min, " + predictTime2 + "mins";
  }
  else if (predictTime1 != "1" && predictTime2 == "1"){
  return busNum + " : " + predictTime1 + "mins, " + predictTime2 + "min";
  }  
  
}

void requestWeatherApi() {

  String str = "GET /wid/queryDFSRSS.jsp?zone=4119060300"; // 부천지역의 날씨 정보
  str.concat(" HTTP/1.1\r\nHost:www.kma.go.kr\r\nConnection: close\r\n\r\n");  

  if(client.connect(host_2, httpPort)){
  Serial.println();
  Serial.println("connected");
  Serial.print(str);
  client.print(str);
  client.println();
 
  cmdSize = str.length();
 
  client.println("AT+CIPSTART=\"TCP\",\"www.kma.go.kr\",80");
  delay(500);
  client.print("AT+CIPSEND=");
  delay(500);
  client.println(cmdSize);
  delay(500);
  client.println(str);
  }
  else {
    Serial.println("Connection Failed: ");
    return;
  } 
}

String parseWeatherApi(String Weather) {
  
  int i=0;
  String temp;
  String wfEn;
  String reh;
  String tmp_str;

  while(client.available()){
    
    //라인을 기준으로 문자열을 저장한다.
    String line = client.readStringUntil('\n');

      i= line.indexOf("</temp>");

      if(i>0){
        tmp_str="<temp>";
        temp = line.substring(line.indexOf(tmp_str)+tmp_str.length(),i);
      }

      i= line.indexOf("</wfEn>");

      if(i>0){
        tmp_str="<wfEn>";
        wfEn = line.substring(line.indexOf(tmp_str)+tmp_str.length(),i);
      }

      i= line.indexOf("</reh>");

      if(i>0){
        tmp_str="<reh>";
        reh = line.substring(line.indexOf(tmp_str)+tmp_str.length(),i);
      }
    }
  return wfEn + ", " + temp + "C, " + reh + "%";
}

void get_location() {
  
  myLocation.getLocation(); 
  
  LAT = String(myLocation.latitude);
  LONG = String(myLocation.longitude); 
 
  Serial.println("-------------------------");
  Serial.print("Latitude = ");     Serial.println(myLocation.latitude);
  Serial.print("Longitude = ");    Serial.println(myLocation.longitude);
  Serial.println("-------------------------");

  return;
}
