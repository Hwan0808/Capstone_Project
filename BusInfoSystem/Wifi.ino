#include <ESP8266WiFi.h>
#define GMAP_API_KEY String ("AIzaSyBqja_I-OFCSNvQq6BCWyayxl5-LgjkBJw") // Google Map API Key

boolean connect_ap(char* ssid, char* password) { // 와이파이 연결 하기
  
  int count = 30; // 최대 30 회 연결 시도 중 wifi 연결하면 성공, 아니면 실패
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    
    delay(500);
    Serial.print(".");
    wifi_oled();
    if (!count--) {
      Serial.print("\nNO WIFI");
      return(false);
    }
  }
  Got_wifi();
  
  previousMillis = millis();
  Serial.print("\nGot WiFi, IP address: ");
  Serial.println(WiFi.localIP());
  Serial.write(Serial.read());
  return(true);
}

void handleRoot1() { // 루트에 접속할때 실행할 내용 (웹서버 동작시에 실행하는 코드)

  String webpage = "<!DOCTYPE html><html><head><meta charset=\"utf-8\"><meta http-equiv=\"refresh\" content=\"10\" charset=utf-8\"><title>버스커버스커 1.0</title>";
  webpage += "<link rel=\"preconnect\" href=\"https://fonts.googleapis.com\"> <link rel=\"preconnect\" href=\"https://fonts.gstatic.com\" crossorigin>";
  webpage += "<link href=\"https://fonts.googleapis.com/css2?family=Hahmlet&display=swap\" rel=\"stylesheet\">";
  webpage += "<style> * { font-family: 'Hahmlet', serif; } a:link {color: blue; background-color: none; text-decoration: none;} a:hover {text-decoration: underline;}";
  webpage += "table {border: 2px solid; border-collapse: collapse;} th, td {border: 1px solid black; text-align: center;} </style> </head>";
  
  webpage += "<body> <h1 style = font-size:300%; ALIGN=CENTER>버스커버스커 1.0</h1>";
  
  webpage += "<div id=\"map\" style=\"width:50%; height:350px; margin: 0 auto;\"></div>";
  webpage += "<script type=\"text/javascript\"> function myMap() { ";
  webpage += "var myCenter = new google.maps.LatLng(" + LAT_value + " , " + LONG_value + ");"; 
  webpage += "var mapCanvas = document.getElementById(\"map\");";
  webpage += "var mapOptions = {center: myCenter, zoom: 15};";
  webpage += "var map = new google.maps.Map(mapCanvas, mapOptions);"; 
  webpage += "var marker = new google.maps.Marker({position:myCenter});";
  webpage += "marker.setMap(map); } </script>";

  webpage += "<script src=\"https://maps.googleapis.com/maps/api/js?key=" + GMAP_API_KEY + "&callback=myMap\"></script>";

  webpage += "<table ALIGN=CENTER style = width:50% >";
  webpage += "<tr><th colspan=\"2\" style=\"color:white; background-color:teal;\">위치 세부사항</th></tr>";
  webpage += "<tr><th>95번 버스</th> <td>";
  webpage += result_95;
  webpage += "</td></tr><tr><th>56번 버스</th> <td>";
  webpage += result_56;
  webpage += "</td></tr><tr><th>60번 버스</th> <td>";
  webpage += result_60;
  webpage += "</td></tr><tr><th>날씨(온도/습도)</th> <td>";
  webpage += Weather;
  webpage += "</td></tr></table> ";
  webpage += "<p ALIGN=CENTER><a href=\"http://www.gbis.go.kr/gbis2014/schBus.action?mapTabCd=3\">경기도 실시간 버스 정보시스템</a><br></p>";
  webpage += "<p ALIGN=CENTER> Created By buskerbusker </p>";
  webpage += "<p ALIGN=CENTER> Copyright <a href=\"https://github.com/Hwan0808\">https://github.com/Hwan0808</a> All rights reserved.</p>";
  webpage += "</body></html> \n";
  
  webpage += "<!-- clock widget start --> <script type=\"text/javascript\">";
  webpage += "var css_file=document.createElement(\"link\");"; 
  webpage += "css_file.setAttribute(\"rel\",\"stylesheet\");"; 
  webpage += "css_file.setAttribute(\"type\",\"text/css\");"; 
  webpage += "css_file.setAttribute(\"href\",\"https://s.bookcdn.com//css/cl/bw-cl-120x45.css?v=0.0.1\");"; 
  webpage += "document.getElementsByTagName(\"head\")[0].appendChild(css_file); </script>";
  webpage += "<div id=\"tw_6_1819623442\"><div style=\"width:130px; height:45px; margin: 0 auto;\">";
  webpage += "<br/></div></div>";
  webpage += "<script type=\"text/javascript\"> function setWidgetData_1819623442(data){ if(typeof(data) != 'undefined' && data.results.length > 0) { for(var i = 0; i < data.results.length; ++i)";
  webpage += "{ var objMainBlock = ''; var params = data.results[i]; objMainBlock = document.getElementById('tw_'+params.widget_type+'_'+params.widget_id);";
  webpage += "if(objMainBlock !== null) objMainBlock.innerHTML = params.html_code; } } }";
  webpage += "var clock_timer_1819623442 = -1;";
  webpage += "widgetSrc = \"https://widgets.booked.net/time/info?ver=2;domid=;type=6;id=1819623442;scode=124;city_id=18406;wlangid=1;mode=0;details=0;background=ffffff;border_color=ffffff;color=826d82;add_background=a0a1a1;add_color=000000;head_color=ffffff;border=0;transparent=0\"; var widgetUrl = location.href; widgetSrc += '&ref=' + widgetUrl; var wstrackId = \"\"; if (wstrackId) { widgetSrc += ';wstrackId=' + wstrackId + ';' } var timeBookedScript = document.createElement(\"script\"); timeBookedScript.setAttribute(\"type\", \"text/javascript\"); timeBookedScript.src = widgetSrc; document.body.appendChild(timeBookedScript); </script> <!-- clock widget end -->";
  webpage += "</script>";
  
  server.send(200,"text/html",webpage);
  delay(100);
 
}
void handleRoot2() { // 루트에 접속할때 실행할 내용 (웹서버 동작시에 실행하는 코드)

  String webpage = "<!DOCTYPE html><html><head><meta charset=\"utf-8\"><meta http-equiv=\"refresh\" content=\"10\" charset=utf-8\"><title>버스커버스커 1.0</title>";
  webpage += "<link rel=\"preconnect\" href=\"https://fonts.googleapis.com\"> <link rel=\"preconnect\" href=\"https://fonts.gstatic.com\" crossorigin>";
  webpage += "<link href=\"https://fonts.googleapis.com/css2?family=Hahmlet&display=swap\" rel=\"stylesheet\">";
  webpage += "<style> * { font-family: 'Hahmlet', serif; } a:link {color: blue; background-color: none; text-decoration: none;} a:hover {text-decoration: underline;}";
  webpage += "table {border: 2px solid; border-collapse: collapse;} th, td {border: 1px solid black; text-align: center;} </style> </head>";
  
  webpage += "<body> <h1 style = font-size:300%; ALIGN=CENTER>버스커버스커 1.0</h1>";
  
  webpage += "<div id=\"map\" style=\"width:50%; height:350px; margin: 0 auto;\"></div>";
  webpage += "<script type=\"text/javascript\"> function myMap() { ";
  webpage += "var myCenter = new google.maps.LatLng(" + LAT_value + " , " + LONG_value + ");"; 
  webpage += "var mapCanvas = document.getElementById(\"map\");";
  webpage += "var mapOptions = {center: myCenter, zoom: 15};";
  webpage += "var map = new google.maps.Map(mapCanvas, mapOptions);"; 
  webpage += "var marker = new google.maps.Marker({position:myCenter});";
  webpage += "marker.setMap(map); } </script>";

  webpage += "<script src=\"https://maps.googleapis.com/maps/api/js?key=" + GMAP_API_KEY + "&callback=myMap\"></script>";

  webpage += "<table ALIGN=CENTER style = width:50% >";
  webpage += "<tr><th colspan=\"2\" style=\"color:white; background-color:teal;\">위치 세부사항</th></tr>";
  webpage += "<tr><th>1-2번 버스</th> <td>";
  webpage += result_1_2;
  webpage += "</td></tr><tr><th>1-5번 버스</th> <td>";
  webpage += result_1_5;
  webpage += "</td></tr><tr><th>5번 버스</th> <td>";
  webpage += result_5;
  webpage += "</td></tr><tr><th>날씨(온도/습도)</th> <td>";
  webpage += Weather;
  webpage += "</td></tr></table> ";
  webpage += "<p ALIGN=CENTER><a href=\"http://www.gbis.go.kr/gbis2014/schBus.action?mapTabCd=3\">경기도 실시간 버스 정보시스템</a><br></p>";
  webpage += "<p ALIGN=CENTER> Created By buskerbusker </p>";
  webpage += "<p ALIGN=CENTER> Copyright <a href=\"https://github.com/Hwan0808\">https://github.com/Hwan0808</a> All rights reserved.</p>";
  webpage += "</body></html> \n";
  
  webpage += "<!-- clock widget start --> <script type=\"text/javascript\">";
  webpage += "var css_file=document.createElement(\"link\");"; 
  webpage += "css_file.setAttribute(\"rel\",\"stylesheet\");"; 
  webpage += "css_file.setAttribute(\"type\",\"text/css\");"; 
  webpage += "css_file.setAttribute(\"href\",\"https://s.bookcdn.com//css/cl/bw-cl-120x45.css?v=0.0.1\");"; 
  webpage += "document.getElementsByTagName(\"head\")[0].appendChild(css_file); </script>";
  webpage += "<div id=\"tw_6_1819623442\"><div style=\"width:130px; height:45px; margin: 0 auto;\">";
  webpage += "<br/></div></div>";
  webpage += "<script type=\"text/javascript\"> function setWidgetData_1819623442(data){ if(typeof(data) != 'undefined' && data.results.length > 0) { for(var i = 0; i < data.results.length; ++i)";
  webpage += "{ var objMainBlock = ''; var params = data.results[i]; objMainBlock = document.getElementById('tw_'+params.widget_type+'_'+params.widget_id);";
  webpage += "if(objMainBlock !== null) objMainBlock.innerHTML = params.html_code; } } }";
  webpage += "var clock_timer_1819623442 = -1;";
  webpage += "widgetSrc = \"https://widgets.booked.net/time/info?ver=2;domid=;type=6;id=1819623442;scode=124;city_id=18406;wlangid=1;mode=0;details=0;background=ffffff;border_color=ffffff;color=826d82;add_background=a0a1a1;add_color=000000;head_color=ffffff;border=0;transparent=0\"; var widgetUrl = location.href; widgetSrc += '&ref=' + widgetUrl; var wstrackId = \"\"; if (wstrackId) { widgetSrc += ';wstrackId=' + wstrackId + ';' } var timeBookedScript = document.createElement(\"script\"); timeBookedScript.setAttribute(\"type\", \"text/javascript\"); timeBookedScript.src = widgetSrc; document.body.appendChild(timeBookedScript); </script> <!-- clock widget end -->";
  webpage += "</script>";
  
  server.send(200,"text/html",webpage);
  delay(100);
 
}

void handleRoot3() { // 루트에 접속할때 실행할 내용 (웹서버 동작시에 실행하는 코드)

  String webpage = "<!DOCTYPE html><html><head><meta charset=\"utf-8\"><meta http-equiv=\"refresh\" content=\"10\" charset=utf-8\"><title>버스커버스커 1.0</title>";
  webpage += "<link rel=\"preconnect\" href=\"https://fonts.googleapis.com\"> <link rel=\"preconnect\" href=\"https://fonts.gstatic.com\" crossorigin>";
  webpage += "<link href=\"https://fonts.googleapis.com/css2?family=Hahmlet&display=swap\" rel=\"stylesheet\">";
  webpage += "<style> * { font-family: 'Hahmlet', serif; } a:link {color: blue; background-color: none; text-decoration: none;} a:hover {text-decoration: underline;}";
  webpage += "table {border: 2px solid; border-collapse: collapse;} th, td {border: 1px solid black; text-align: center;} </style> </head>";
  
  webpage += "<body> <h1 style = font-size:300%; ALIGN=CENTER>버스커버스커 1.0</h1>";
  
  webpage += "<div id=\"map\" style=\"width:50%; height:350px; margin: 0 auto;\"></div>";
  webpage += "<script type=\"text/javascript\"> function myMap() { ";
  webpage += "var myCenter = new google.maps.LatLng(" + LAT_value + " , " + LONG_value + ");"; 
  webpage += "var mapCanvas = document.getElementById(\"map\");";
  webpage += "var mapOptions = {center: myCenter, zoom: 15};";
  webpage += "var map = new google.maps.Map(mapCanvas, mapOptions);"; 
  webpage += "var marker = new google.maps.Marker({position:myCenter});";
  webpage += "marker.setMap(map); } </script>";

  webpage += "<script src=\"https://maps.googleapis.com/maps/api/js?key=" + GMAP_API_KEY + "&callback=myMap\"></script>";

  webpage += "<table ALIGN=CENTER style = width:50% >";
  webpage += "<tr><th colspan=\"2\" style=\"color:white; background-color:teal;\">위치 세부사항</th></tr>";
  webpage += "<tr><th>3300번 버스</th> <td>";
  webpage += result_3300;
  webpage += "</td></tr><tr><th>3301번 버스</th> <td>";
  webpage += result_3301;
  webpage += "</td></tr><tr><th>530번 버스</th> <td>";
  webpage += result_530;
  webpage += "</td></tr><tr><th>날씨(온도/습도)</th> <td>";
  webpage += Weather;
  webpage += "</td></tr></table> ";
  webpage += "<p ALIGN=CENTER><a href=\"http://www.gbis.go.kr/gbis2014/schBus.action?mapTabCd=3\">경기도 실시간 버스 정보시스템</a><br></p>";
  webpage += "<p ALIGN=CENTER> Created By buskerbusker </p>";
  webpage += "<p ALIGN=CENTER> Copyright <a href=\"https://github.com/Hwan0808\">https://github.com/Hwan0808</a> All rights reserved.</p>";
  webpage += "</body></html> \n";
  
  webpage += "<!-- clock widget start --> <script type=\"text/javascript\">";
  webpage += "var css_file=document.createElement(\"link\");"; 
  webpage += "css_file.setAttribute(\"rel\",\"stylesheet\");"; 
  webpage += "css_file.setAttribute(\"type\",\"text/css\");"; 
  webpage += "css_file.setAttribute(\"href\",\"https://s.bookcdn.com//css/cl/bw-cl-120x45.css?v=0.0.1\");"; 
  webpage += "document.getElementsByTagName(\"head\")[0].appendChild(css_file); </script>";
  webpage += "<div id=\"tw_6_1819623442\"><div style=\"width:130px; height:45px; margin: 0 auto;\">";
  webpage += "<br/></div></div>";
  webpage += "<script type=\"text/javascript\"> function setWidgetData_1819623442(data){ if(typeof(data) != 'undefined' && data.results.length > 0) { for(var i = 0; i < data.results.length; ++i)";
  webpage += "{ var objMainBlock = ''; var params = data.results[i]; objMainBlock = document.getElementById('tw_'+params.widget_type+'_'+params.widget_id);";
  webpage += "if(objMainBlock !== null) objMainBlock.innerHTML = params.html_code; } } }";
  webpage += "var clock_timer_1819623442 = -1;";
  webpage += "widgetSrc = \"https://widgets.booked.net/time/info?ver=2;domid=;type=6;id=1819623442;scode=124;city_id=18406;wlangid=1;mode=0;details=0;background=ffffff;border_color=ffffff;color=826d82;add_background=a0a1a1;add_color=000000;head_color=ffffff;border=0;transparent=0\"; var widgetUrl = location.href; widgetSrc += '&ref=' + widgetUrl; var wstrackId = \"\"; if (wstrackId) { widgetSrc += ';wstrackId=' + wstrackId + ';' } var timeBookedScript = document.createElement(\"script\"); timeBookedScript.setAttribute(\"type\", \"text/javascript\"); timeBookedScript.src = widgetSrc; document.body.appendChild(timeBookedScript); </script> <!-- clock widget end -->";
  webpage += "</script>";
  
  server.send(200,"text/html",webpage);
  delay(100);
 
}
