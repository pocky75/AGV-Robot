#include <Arduino.h>
#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>

// ==========================================================
// 핀 정의 및 상수
// ==========================================================
#define SERVO_DOWN  25
#define SERVO_UP    180
#define PIN_SERVO   9

#define BLACK 1
#define WHITE 0
#define IR_REF_RANGE 650

#define WRP 6
#define WRD 8
#define WLP 5
#define WLD 7

#define IR_LEFT A6
#define IR_RIGHT A7

#define FORWARD 0
#define BACKWARD 1

#define BUZZER_PIN 3
#define RFID_SS_PIN 2
#define RFID_RST_PIN 4

// ==========================================================
// 전역 변수 및 PID 제어 게인
// ==========================================================
float Power1Ratio = 0.99; // 왼쪽 모터 속도 보정비율
float Power2Ratio = 1.00; // 오른쪽 모터 속도 보정비율

// PID 제어 변수
float Kp = 25.0;  // 비례 게인 (P): 현재 오차에 비례하여 보정
float Ki = 0.0;   // 적분 게인 (I): 누적 오차 보정 (2센서 환경에서는 0 권장)
float Kd = 15.0;  // 미분 게인 (D): 오차 변화율 예측 (진동/출렁임 방지)

float prev_error = 0.0;
float integral = 0.0;

bool isLifterUp = false;

Servo servo;
MFRC522 mfrc522(RFID_SS_PIN, RFID_RST_PIN);

// ==========================================================
// 함수 선언
// ==========================================================
void drive(int dir1, int power1, int dir2, int power2);
void moveIrForwardPID(int basePower);
void moveIrBackward(int power);
void rotateLeft(int power);
void rotateRight(int power);
void rotate180(int power);
void Stop();
void bw(int result[]);
void buzzer(int val, int time);
void lifterUp();
void lifterDown();
void waitCardTag();

// ==========================================================
// 초기화 함수
// ==========================================================
void setup() {
  Serial.begin(9600);

  SPI.begin();
  mfrc522.PCD_Init();

  pinMode(WRP, OUTPUT);
  pinMode(WRD, OUTPUT);
  pinMode(WLP, OUTPUT);
  pinMode(WLD, OUTPUT);

  // 초기 테스트 시퀀스
  waitCardTag(); 
  lifterUp();
  delay(500);
  lifterDown();

  waitCardTag();

  // PID 기반 라인 트레이싱 주행
  moveIrForwardPID(100);
  moveIrForwardPID(100);
  moveIrForwardPID(100);
  moveIrForwardPID(80);
  rotateLeft(60);
  moveIrForwardPID(100);
  moveIrForwardPID(100);
  moveIrForwardPID(100);
  moveIrForwardPID(100);
  moveIrForwardPID(100);
  moveIrForwardPID(100);
  moveIrForwardPID(80);
  
  lifterUp();
  rotate180(60);

  waitCardTag();
  moveIrForwardPID(80);
  waitCardTag();
  moveIrForwardPID(80);
  waitCardTag();
  rotateRight(60);
  waitCardTag();
  moveIrForwardPID(80);
  waitCardTag();
  rotateLeft(60);

  moveIrForwardPID(100);
  moveIrForwardPID(100);
  moveIrForwardPID(100);
  moveIrForwardPID(100);
  moveIrForwardPID(100);
  moveIrForwardPID(100);
  moveIrForwardPID(80);

  lifterDown();
}

void loop() {
  // 반복 실행 로직이 필요한 경우 여기에 추가
}

// ==========================================================
// 핵심 제어 함수들
// ==========================================================
void drive(int dir1, int power1, int dir2, int power2) {
  boolean dirHighLow1 = (dir1 == FORWARD) ? HIGH : LOW;
  boolean dirHighLow2 = (dir2 == FORWARD) ? LOW : HIGH;
  
  int adjPower1 = power1 * Power1Ratio;
  int adjPower2 = power2 * Power2Ratio;

  digitalWrite(WLD, dirHighLow1);
  analogWrite(WLP, adjPower1);

  digitalWrite(WRD, dirHighLow2);
  analogWrite(WRP, adjPower2);
}

// ✅ 신규 PID 제어 전진 함수
void moveIrForwardPID(int basePower) { 
  int irVal[2];
  float error = 0.0;
  
  drive(FORWARD, basePower * Power1Ratio, FORWARD, basePower * Power2Ratio); 
  delay(10);

  while (true) {
    bw(irVal);

    // 1. 오차(Error) 계산
    if (irVal[0] == BLACK && irVal[1] == WHITE) {
      error = -1.0; // 오른쪽 이탈 → 왼쪽 보정
    } 
    else if (irVal[0] == WHITE && irVal[1] == BLACK) {
      error = 1.0;  // 왼쪽 이탈 → 오른쪽 보정
    } 
    else if (irVal[0] == BLACK && irVal[1] == BLACK) {
      int delayVal = isLifterUp ? 150 : 100;
      buzzer(262, delayVal);
      break; // 교차로 감지 시 종료
    } 
    else {
      error = 0.0; // 중앙 주행
    }

    // 2. PID 연산
    integral += error;
    integral = constrain(integral, -5.0, 5.0); // Windup 방지
    
    float derivative = error - prev_error;
    float pid_output = (Kp * error) + (Ki * integral) + (Kd * derivative);
    prev_error = error;

    // 3. 모터 속도 계산 및 제한 (0 ~ 255)
    int leftPower = constrain(basePower + pid_output, 0, 255);
    int rightPower = constrain(basePower - pid_output, 0, 255);

    // 4. 하드웨어 보정 비율 적용 후 구동
    drive(FORWARD, leftPower * Power1Ratio, FORWARD, rightPower * Power2Ratio);
    delay(10); 
  }
  Stop();
}

/* 
// [주석 처리됨] 기존 단순 보정 함수 (비교용)
void moveIrForward(int power) { 
  int irVal[2];
  drive(FORWARD, power, FORWARD, power); 
  delay(10);
  while(true){
    bw(irVal);
    if(irVal[0] == BLACK && irVal[1] == BLACK){
      int delayVal = isLifterUp ? 150 : 100;
      buzzer(262, delayVal);
      break;
    }
    if(irVal[0] == WHITE && irVal[1] == WHITE){
      drive(FORWARD, power, FORWARD, power);
    }
    else if(irVal[0] == BLACK && irVal[1] == WHITE){
      drive(FORWARD, power, FORWARD, power+20);
    }
    else if(irVal[0] == WHITE && irVal[1] == BLACK){
      drive(FORWARD, power+20, FORWARD, power);
    }
  }
  Stop();
}
*/

void moveIrBackward(int power) { 
  drive(BACKWARD, power, BACKWARD, power); 
}

void rotateLeft(int power) { 
  drive(BACKWARD, power, FORWARD, power); 
  delay(700); 
  Stop();
}

void rotateRight(int power) { 
  drive(FORWARD, power, BACKWARD, power); 
  delay(700); 
  Stop();
}

void rotate180(int power) { 
  drive(FORWARD, power, BACKWARD, power); 
  delay(1500); 
  Stop();
}

void Stop() {
  analogWrite(WLP, 0);
  analogWrite(WRP, 0);
}

void bw(int result[]) {
  int ir_left = analogRead(IR_LEFT);
  int ir_right = analogRead(IR_RIGHT);

  result[0] = (ir_left < IR_REF_RANGE) ? WHITE : BLACK;
  result[1] = (ir_right < IR_REF_RANGE) ? WHITE : BLACK;
}

void buzzer(int val, int time) {
  tone(BUZZER_PIN, val);
  delay(time);
  noTone(BUZZER_PIN);
}

void lifterUp() {
  servo.attach(PIN_SERVO);
  delay(10);
  servo.write(SERVO_UP);
  delay(300);
  servo.detach();
  delay(10);
  isLifterUp = true;
}

void lifterDown() {
  servo.attach(PIN_SERVO);
  delay(10);
  servo.write(SERVO_DOWN);
  delay(300);
  servo.detach();
  delay(10);
  isLifterUp = false;
}

void waitCardTag() {
  while (!mfrc522.PICC_IsNewCardPresent()) {
    delay(100);
  }
  if (mfrc522.PICC_ReadCardSerial()) {
    buzzer(1000, 100); // 인식 성공 피드백
  } else {
    delay(500);
  }
}