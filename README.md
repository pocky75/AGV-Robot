# AGV-Robot

# 🤖 AGV 물류 이송 로봇 (WCRC 2025 참가작)

<div align="center">

![C](https://img.shields.io/badge/C-Arduino-blue.svg)
![PlatformIO](https://img.shields.io/badge/PlatformIO-VSCode-orange.svg)
![RFID](https://img.shields.io/badge/RFID-Sensor-green.svg)
![Award](https://img.shields.io/badge/Award-WCRC_2025_우수상-gold.svg)
![License](https://img.shields.io/badge/License-MIT-yellow.svg)

**RFID 기반 자율 물류 이송 AGV 시스템**

🏆 **2025 WCRC 물류로봇 경진대회 - 물류로봇1(이동) 부문 우수상 (대구테크노파크 원장상) 수상작**

</div>

---

## 📋 프로젝트 소개

본 프로젝트는 **2025 WCRC(World Creative Robot Contest) 물류로봇 경진대회** '물류로봇1(이동)' 부문에 참가하여 **우수상(대구테크노파크 원장상)** 을 수상한 자율 주행 물류 이송 로봇(AGV)입니다.

RFID 센서를 활용한 물류 정보 인식과 **PID 제어 기반의 라인 트레이싱**을 결합하여, 지정된 물류를 출발지에서 도착지까지 안정적으로 이송하는 시스템을 구현했습니다.

### 🏆 수상 내역
- **대회명**: 2025 WCRC 물류로봇 경진대회 (World Creative Robot Contest)
- **주최**: 과학기술정보통신부
- **주관**: 한국폴리텍대학 영남융합기술캠퍼스
- **일시**: 2025.05.29. ~ 2025.05.30.
- **장소**: 한국폴리텍대학 영남융합기술캠퍼스 대학본부 1층 대강당
- **부문**: 물류로봇1 (이동) - 대학일반 부문
- **수상**: **우수상** (대구테크노파크 원장상) 🥈

---

## 🎯 대회 미션

### 물류로봇1 (이동) 부문 미션 내용
> **2대의 로봇이 물류의 RFID 정보를 취득하여, 물류 도착 지점으로 이송하는 미션을 수행**

- RFID 센서를 통해 물류 박스에 기록된 정보(도착지, 우선순위 등)를 실시간으로 읽기
- 읽은 정보를 바탕으로 해당 물류를 올바른 도착 구역까지 자율 이송
- 정해진 코스(라인)를 따라 안정적으로 주행하며 미션 완수

---

## ✨ 주요 특징

- 📡 **RFID 기반 물류 인식**: 물류 박스의 RFID 태그를 실시간으로 읽어 도착지 정보 획득
- 🛣️ **PID 제어 기반 라인 트레이싱**: PID 알고리즘을 활용한 정밀한 라인 추종 제어
- ⚙️ **4륜 차동 구동 방식**: 대회 제공 2륜 로봇을 4륜으로 개조하여 안정성 및 하중 지지력 향상
- 🔵 **캐스터 볼 지지대**: 뒤쪽에 캐스터 볼(쇠구슬)을 사용하여 높이 조절 및 안정적인 지지
- 🤝 **2대 로봇 협업**: 2대의 로봇이 동시에 작동하여 물류 이송 효율 극대화
- 💻 **VSCode + PlatformIO 개발 환경**: Arduino 기반 펌웨어를 VSCode에서 효율적으로 개발 및 디버깅

---

## 🛠️ 기술 스택

### 🖥️ 하드웨어
| 분류 | 구성 | 설명 |
|------|------|------|
| **메인 컨트롤러** | Arduino | 로봇 제어 및 센서 데이터 처리 |
| **개발 환경** | VSCode + PlatformIO | 코드 작성, 컴파일, 업로드 통합 환경 |
| **구동 방식** | **4륜 차동 구동** | 좌우 2개씩 총 4개 바퀴, 2개 모터로 제어 |
| **구동 모터** | DC 모터 + 엔코더 (2개) | 좌우 독립 제어, 정밀한 속도 및 위치 제어 |
| **RFID 센서** | RC522 RFID 모듈 | 물류 박스 태그 인식 (13.56MHz) |
| **라인 센서** | IR 센서 어레이 (다채널) | 바닥 라인 추적 및 편차 감지 |
| **바퀴 구성** | **4륜** (좌우 2개씩) + 캐스터 볼 (뒤쪽) | 4개 바퀴로 하중 분산, 캐스터 볼로 방향 전환 |
| **전원** | Li-Po 배터리 11.1V | 안정적인 전원 공급 |

### 💻 소프트웨어
| 분류 | 기술 | 설명 |
|------|------|------|
| **언어** | C (Arduino) | 펌웨어 및 제어 로직 |
| **개발 도구** | VSCode + PlatformIO | 통합 개발 환경 |
| **제어 알고리즘** | **PID 제어** | 라인 추종 정밀도 향상 (비례·적분·미분 제어) |
| **통신** | RFID 프로토콜 (ISO 14443A) | 물류 태그 읽기/쓰기 |
| **상태 관리** | FSM (Finite State Machine) | 미션 단계별 상태 전환 관리 |

---

## 🏗️ 시스템 아키텍처

### 데이터 흐름


---

## 🔧 로봇 구조 (4륜 차동 구동 개조)

대회에서 제공하는 규격 로봇(2륜)을 기반으로, **주행 안정성과 하중 지지력 향상**을 위해 4륜으로 개조했습니다.

### 개조 배경
- **대회 제공 로봇**: 2륜 차동 구동 (양쪽에 1개씩 총 2개 바퀴)
- **문제점**: 물류 적재 시 무게 중심 불안정, 라인 추종 시 흔들림 발생
- **해결책**: 양쪽에 1개씩 바퀴를 추가하여 **4륜 구조**로 개조

### 개조 내용
- **바퀴 추가**: 기존 2륜(양쪽 1개씩)에 양쪽 1개씩 추가하여 **총 4륜**(양쪽 2개씩)으로 변경
- **모터 연결**: 2개의 DC 모터로 좌우 2개 바퀴를 각각 연결 (동일 축 동기화)
- **지지대**: 뒤쪽에 캐스터 볼(쇠구슬)을 장착하여 로봇의 높이를 조절하고 안정적으로 지지

### 4륜 개조의 장점
✅ **하중 분산**: 물류 적재 시 4개 바퀴로 하중이 분산되어 안정성 향상  
✅ **주행 안정성**: 코너링 및 직진 주행 시 흔들림 감소  
✅ **라인 추종 정밀도**: 바퀴가 4개이므로 바닥 접지력이 향상되어 라인 센서 안정성 확보  
✅ **PID 제어 최적화**: 안정적인 구동 기반으로 PID 튜닝 용이  
✅ **내구성**: 바퀴 1개에 가해지는 하중이 절반으로 감소하여 마모 감소

---

## 💻 개발 환경 (VSCode + PlatformIO)

Arduino IDE 대신 **VSCode + PlatformIO**를 사용하여 효율적인 개발 환경을 구축했습니다.

### 장점
- 🎨 **코드 하이라이팅 및 자동완성**: C 문법 지원으로 개발 생산성 향상
- 🐛 **디버깅 용이**: 통합 터미널과 시리얼 모니터로 실시간 디버깅
- 📦 **라이브러리 관리**: `platformio.ini`에서 의존성 라이브러리 자동 관리
- 🔀 **Git 연동**: VSCode 내장 Git 기능으로 버전 관리 편리

## 핵심 제어 로직

본 AGV 로봇의 핵심 알고리즘은 크게 **경로 실행, 라인 트레이싱 보정, 가변 회전, RFID 인식**으로 구성됩니다.

### 1. 경로 실행 및 명령어 
문자열 명령어(`F`, `L`, `R`, `U`, `D` 등)를 파싱하여 로봇의 주행을 제어합니다.
```
void executePath(const char* path, int basePower) {
  int power = basePower;
  for (int i = 0; path[i] != '\0'; i++) {
    char cmd = path[i];
    switch (cmd) {
      case 'F': moveIrForward(power); break;   // 전진
      case 'L': rotateLeft(80); break;         // 좌회전
      case 'R': rotateRight(80); break;        // 우회전
      case 'U': lifterUp(); break;             // 리프트 업
      case 'D': lifterDown(); break;           // 리프트 다운
      case 'W': waitCardTag(); break;          // RFID 태그 대기
    }
  }
  Stop();
}
```
### 2. IR 센서 기반 라인 트레이싱 보정 코드
```
void moveIrForward(int power) { 
  while (true) {
    bw(irVal); // IR 센서 값 읽기
    
    if (irVal[0] == BLACK && irVal[1] == BLACK) {
      buzzer(262, isLifterUp ? 50 : 67);
      break;
    }
    
    if (irVal[0] == BLACK && irVal[1] == WHITE) {
      if (isLifterUp) drive(FORWARD, power - (7 + power/15), FORWARD, power);
      else            drive(FORWARD, power - (13 + power/8), FORWARD, power);
    } 
    else if (irVal[0] == WHITE && irVal[1] == BLACK) {
      if (isLifterUp) drive(FORWARD, power, FORWARD, power - (7 + power/15));
      else            drive(FORWARD, power, FORWARD, power - (13 + power/8));
    }
  }
}
```
### 3. 상태 기반 가변 회전
```
void rotateLeft(int power) {
  unsigned long startTime = millis();
  unsigned long rotateTime = isLifterUp ? 564 : 548; 

  while (millis() - startTime < rotateTime) {
    drive(BACKWARD, power, FORWARD, power); 
  }
  Stop();
}
```
### 4. RFID 태그 인식 및 대기
```
void waitCardTag() {
  while (true) {
    if (!mfrc522.PICC_IsNewCardPresent()) { delay(100); continue; }
    if (mfrc522.PICC_ReadCardSerial()) {
      buzzer(1000, 100); 
      break;
    }
    delay(100);
  }
}
```
### 시연영상 및 실행화면

# 시연영상
https://github.com/user-attachments/assets/80266583-f823-4c2e-b8cb-82a7a4f56452


# 실행화면
 vscode + platformIO 
# 시리얼모니터 연결성공로그 

# 시리얼통신 연결확인

