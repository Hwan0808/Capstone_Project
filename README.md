# Capstone_Project

종합설계 프로젝트 팀프로젝트 <br>

이태환, 김하윤, 최창환

## 프로젝트 제목

GPS를 이용한 실시간 버스정보알리미

## 프로젝트 목표

버스정보포털에 공공데이터를 가공하여 사용자가 직관적으로 이해할 수 있도록 어플로 구현한다.<br>

- 아두이노(UNO)와, GPS모듈, WIFI모듈을 이용하여 회로도를 구성하고 실시간 버스정보를 받아오는 시스템을 구성한다.
- 아두이노로부터 받아온 데이터를 파싱하는 작업을 구현하고 안드로이드 스튜디오를 활용하여 어플을 제작한다.

## Bug Fix

![image](https://user-images.githubusercontent.com/57865037/161235404-4a173910-ce40-4421-aa1b-06a6459a07dc.png)

![image](https://user-images.githubusercontent.com/57865037/161235380-f4833446-9f39-4ef8-a30b-825f3ba0cbb1.png)

![image](https://user-images.githubusercontent.com/57865037/161235223-a093dce8-329d-48a0-b65a-85eba0b60121.jpg)

## To Do List

1. H/W part

- 아두이노 회로도 설계 - 와이파이 모듈(E12) - L2C OLED 디스플레이 출력
- Fireabase 데이터 연동 - 안드로이드와의 통신을 위한 데이터 가공(파싱)

2. S/W part (안드로이드 어플)

- 프론트 엔드 - UI/UX 구현
- 백 엔드 - Firebase 와의 데이터 연동을 위한 서버 구성

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
