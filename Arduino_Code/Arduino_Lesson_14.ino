#include <Wire.h>
const byte MPU = 0x68, LED_PIN = 8;
void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); Wire.write(0);
  Wire.endTransmission(true);
}
void loop() {
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  if (Wire.endTransmission(false) != 0) return;
  if (Wire.requestFrom(MPU, (uint8_t)6, (uint8_t)true) != 6) return;
  int16_t ax = (Wire.read() << 8) | Wire.read();
  int16_t ay = (Wire.read() << 8) | Wire.read();
  int16_t az = (Wire.read() << 8) | Wire.read();
  float x = ax / 16384.0f;
  float y = ay / 16384.0f;
  float z = az / 16384.0f;
  float roll  = atan2(y, z) * 180.0f / PI;
  float pitch = atan2(-x, sqrt(y*y + z*z)) * 180.0f / PI;
  bool alarm = abs(roll) > 35 || abs(pitch) > 35;
  digitalWrite(LED_PIN, alarm ? HIGH : LOW);
  Serial.print("Roll: "); Serial.print(roll, 1);
  Serial.print(" Pitch: "); Serial.println(pitch, 1);
  delay(200);
}
