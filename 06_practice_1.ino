int led = 9;         
int brightness = 0;  
int fadeAmount = 5;  

void setup() {
  pinMode(led, OUTPUT); 
}

void loop() {
  analogWrite(led, brightness);  

  // 다음 루프에서의 밝기 값 조정
  brightness = brightness + fadeAmount;

  // 밝기 0 or 255 도달시 방향을 전환
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;  
  }

  delay(30);  
}
