# Capstone_Project ⚙️

종합설계 프로젝트 팀프로젝트 <br>

이태환, 김하윤, 최창환

## 프로젝트 제목

GPS를 이용한 실시간 버스정보알리미

## 프로젝트 목표

버스정보포털에 공공데이터를 가공하여 사용자가 직관적으로 이해할 수 있도록 시스템을 구현한다.<br>

- 아두이노(ESP8266[12E])와, GPS모듈, WIFI모듈을 이용하여 회로도를 구성하고 실시간 버스정보를 받아오는 시스템을 구성한다.
- 아두이노로부터 받아온 데이터를 파싱하는 작업을 구현하고 사용자에게 간략하게 보여줄 수 있는 웹페이지를 제작한다.
- pushbullet 앱을 이용하여 푸시알림이 가도록 설계한다.

## 회로 설계도

![image](https://user-images.githubusercontent.com/57865037/168776372-ba141567-fdf4-45b4-9159-1ee9f365278c.png)

## Bug Fix

![image](https://user-images.githubusercontent.com/57865037/162119464-6960a118-9d9f-44d1-a2de-dfe907ebc898.jpeg)

![image](https://user-images.githubusercontent.com/57865037/161235223-a093dce8-329d-48a0-b65a-85eba0b60121.jpg)

## To Do List

1. H/W part

- 아두이노 회로도 설계 → 와이파이 모듈(E12) → L2C OLED 디스플레이 출력

2. S/W part (안드로이드 어플)

- 아두이노로 부터 받아온 데이터를 파싱 → 웹페이지 구현(버스정보/날씨)
- pushbullet 을 활용하여 사용자에게 알림이 갈 수 있도록 구현

3. 아두이노 키트

- 모형 제작

## 주요 알고리즘

- 각종 수정 사항 업로드

## 참고 자료

- https://www.data.go.kr/tcs/dss/selectApiDataDetailView.do?publicDataPk=15080666 경기도 공공 데이터 포털 사이트 버스 정보 (API)
- https://www.data.go.kr/tcs/dss/selectApiDataDetailView.do?publicDataPk=15080346 경기도 공공 데이터 포털 사이트 버스 도착 정보 (API)
- https://www.weather.go.kr/w/index.do 기상청 날씨 누리
- https://bota.tistory.com/1469 실시간 버스도착정보 LCD 화면에 출력하는 방법
- https://blog.naver.com/geniusus/221799048747 PushBullet 사용법
- https://blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=twophase&logNo=220730309094 PushBullet 사용법
- https://www.youtube.com/channel/UCV68qKnBcZ-LR5hWnzCRf_A/search?query=%EC%9B%B9 웹서버 구축 두원공과대학교_김동일 교수님
- https://github.com/kdi6033/arduino/tree/master/1-36-Arduino%2BHtml 웹 서버 구축 (html) 파일 적용하기
