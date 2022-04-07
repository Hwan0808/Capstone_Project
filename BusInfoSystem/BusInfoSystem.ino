 #define serviceKey String ("A44txAbG4xvtwlhJfgd7SIHSndYpwkzy65BpHPG75%2Fdzqhqr%2FSlAjzYldYmYwhwLUPjsxB9PWh37iT10AwRCrg%3D%3D")
 
//API Key

char* ssid = "KT_GiGA_AAE1";
char* password = "edcd6eg366";

const int GBISUPD_INTERVAL = 12000;
const int WEATHER_INTERVAL = 20000;
const char* host_1 = "apis.data.go.kr";
const char* host_2 = "www.kma.go.kr";

const int httpPort = 80;
 
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>  // ESP 8266 웹서버 라이브러리
#include <WiFiClient.h>
WiFiClient client;

ESP8266WebServer server(80);  // 웹서버 오브젝트

int cmdSize = 0;
String busstopID = "210000388"; // 소사역지하차도 버스정류장
 
String rcvbuf;
long currentMillis;
long previousMillis = 0;
boolean wifi_ready;
boolean requestLocker = false;
boolean requestLocker1 = false;
boolean requestLocker2 = true;
boolean requestLocker3 = true;
String result_95;
String result_56;
String result_60;
String Weather;
//String temp;
//String wfEn;
//String reh;

void setup() {
  Serial.begin(115200);
  setup_oled();
  wifi_ready = connect_ap(ssid, password); // 와이파이 연결 하기
  if (!wifi_ready){
    nowifi_oled();
  }
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
 
  if(millis() - previousMillis > GBISUPD_INTERVAL){
    result_95 = parseArrivalTime("95");
    do_oled(0, 11, result_95);
    do_oled(0, 22, result_56);
    do_oled(0, 33, result_60);
    do_oled(0, 44, Weather);
    requestLocker2 = true;
    requestLocker3 = true;
  }
 
  else if(millis() - previousMillis > GBISUPD_INTERVAL - 2000 && requestLocker)
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
 
  else if(millis() - previousMillis > GBISUPD_INTERVAL - 10000 && requestLocker2)
  {
 
    // 60
    requestArrivalTime("210000043", "210000388");
    requestLocker2 = false;
    requestLocker1 = true;
  }
  else if(millis() - previousMillis > WEATHER_INTERVAL - 14000 && requestLocker3)
  {
    // 날씨 정보 받아오기
    requestWeatherApi();
    Weather = parseWeatherApi("Weather");
    requestLocker3 = false;
    requestLocker2 = true;
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
    return busNum + " : End of Service ";
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
        Serial.println(temp); 

      }

      i= line.indexOf("</wfEn>");

      if(i>0){
        tmp_str="<wfEn>";
        wfEn = line.substring(line.indexOf(tmp_str)+tmp_str.length(),i);
        Serial.println(wfEn);  
      }

      i= line.indexOf("</reh>");

      if(i>0){
        tmp_str="<reh>";
        reh = line.substring(line.indexOf(tmp_str)+tmp_str.length(),i);
        Serial.println(reh);  
        break;
      }
    }

  delay(1000);

  return Weather + " : " + wfEn + ", " + temp + "C";

}
