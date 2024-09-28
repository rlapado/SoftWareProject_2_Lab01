const int ledPin = 7; 

void setup() {
  pinMode(ledPin, OUTPUT);  
  Serial.begin(115200);      //플로터 확인을 위해서 
  Serial.println("Setup complete.");
}

void loop() {
  // 처음 1초 동안 LED 켜기
  Serial.println("LED ON (1초)");
  digitalWrite(ledPin, LOW);   // LED ON
  delay(1000);                 // 1초 LED ON
  
  // 다음 1초 동안 5회 깜빡이기
  Serial.println("LED Blink (5회)");
  for (int i = 0; i < 5; i++) {
    digitalWrite(ledPin, HIGH);  // LED OFF
    delay(100);                  // 0.1초
    digitalWrite(ledPin, LOW);   // LED ON
    delay(100);                  // 0.1초    
                                 //총 1초
  }

  // LED를 끄고 종료
  Serial.println("LED OFF");
  digitalWrite(ledPin, HIGH);   // LED OFF

  while (1) { // infinite loop
    
  }
}
