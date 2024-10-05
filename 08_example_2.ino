// Arduino 핀 설정
#define PIN_LED  9
#define PIN_TRIG 12   // 초음파 센서 TRIGGER
#define PIN_ECHO 13   // 초음파 센서 ECHO

// 설정 가능한 매개변수
#define SND_VEL 346.0     // 소리 속도 (24도에서, 단위: m/sec)
#define INTERVAL 25      // 샘플링 간격 (단위: msec)
#define PULSE_DURATION 10 // 초음파 펄스 지속 시간 (단위: usec)
#define _DIST_MIN 100.0   // 측정할 최소 거리 (단위: mm)
#define _DIST_MAX 300.0   // 측정할 최대 거리 (단위: mm)

#define TIMEOUT ((INTERVAL / 2) * 1000.0) // 최대 echo 대기 시간 (단위: usec)
#define SCALE (0.001 * 0.5 * SND_VEL) // 지속 시간을 거리로 변환하는 계수

unsigned long last_sampling_time;   // 단위: msec

void setup() {
  // GPIO 핀 초기화
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_TRIG, OUTPUT);  // 초음파 TRIGGER
  pinMode(PIN_ECHO, INPUT);   // 초음파 ECHO
  digitalWrite(PIN_TRIG, LOW);  // 초음파 센서 끔
  
  // 시리얼 포트 초기화
  Serial.begin(57600);
}

void loop() { 
  float distance;

  // 다음 샘플링 시간까지 대기
  if (millis() < (last_sampling_time + INTERVAL))
    return;

  distance = USS_measure(PIN_TRIG, PIN_ECHO); // 거리 측정

  if ((distance == 0.0) || (distance > _DIST_MAX)) {
    distance = _DIST_MAX + 10.0;    // 최대값 초과 설정
    analogWrite(PIN_LED, 255);      // LED 끔
  } else if (distance < _DIST_MIN) {
    distance = _DIST_MIN - 10.0;    // 최소값 미만 설정
    analogWrite(PIN_LED, 255);      // LED 끔
  } else {    // 설정된 범위 내일 때
    int brightness = calculateBrightness(distance);
    analogWrite(PIN_LED, brightness); // LED 밝기 조절
  }

  // 시리얼 포트에 거리 출력
  Serial.print("Min:");        Serial.print(_DIST_MIN);
  Serial.print(",distance:");  Serial.print(distance);
  Serial.print(",Max:");       Serial.print(_DIST_MAX);
  Serial.println("");
  
  // 마지막 샘플링 시간 업데이트
  last_sampling_time += INTERVAL;
}

// 초음파 센서에서 거리 읽기, 반환값은 mm 단위
float USS_measure(int TRIG, int ECHO)
{
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(PULSE_DURATION);
  digitalWrite(TRIG, LOW);
  
  return pulseIn(ECHO, HIGH, TIMEOUT) * SCALE; // mm 단위로 반환
}

// 거리에 따른 LED 밝기 계산
int calculateBrightness(float distance) {
  if (distance <= 150.0) {
    return map(distance, _DIST_MIN, 150, 255, 128); // 100mm -> 꺼짐, 150mm -> 50% 밝기
  } else {
    return map(distance, 150, _DIST_MAX, 128, 255); // 150mm -> 50% 밝기, 300mm -> 꺼짐
  }
}
