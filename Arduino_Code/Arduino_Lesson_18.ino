#include <Stepper.h>
const int STEPS_PER_REV = 2048; // 教學近似值
Stepper motor(STEPS_PER_REV, 8, 10, 9, 11);
void setup() {
  Serial.begin(9600);
  motor.setSpeed(10);
}
void loop() {
  motor.step(STEPS_PER_REV / 4);  // 約 +90°
  Serial.println("CW +90 approx");
  delay(1000);
  motor.step(-STEPS_PER_REV / 4); // 約 -90°
  Serial.println("CCW -90 approx");
  delay(1000);
}
