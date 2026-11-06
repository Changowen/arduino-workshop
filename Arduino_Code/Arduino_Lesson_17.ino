#include <SoftwareSerial.h>
SoftwareSerial BT(10, 11); // UNO RX, TX
const byte LED_PIN = 8;
void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  Serial.begin(9600);
  BT.begin(9600); // 依 HC-05 資料模式實際鮑率調整
}
void loop() {
  if (BT.available()) {
    char c = (char)BT.read();
    if (c == '1') {
      digitalWrite(LED_PIN, HIGH); BT.println("LED ON");
    } else if (c == '0') {
      digitalWrite(LED_PIN, LOW); BT.println("LED OFF");
    }
  }
}
