const byte TEMP_PIN = A0, FAN_PWM = 5;
const float setpoint = 28.0f;
const float Kp = 32.0f;
unsigned long lastSample = 0;
void setup() {
  pinMode(FAN_PWM, OUTPUT);
  Serial.begin(9600);
}
void loop() {
  if (millis() - lastSample >= 500UL) {
    lastSample = millis();
    int raw = analogRead(TEMP_PIN);
    float tempC = raw * (5.0f / 1023.0f) * 100.0f;
    int pwm = constrain((int)((tempC - setpoint) * Kp), 0, 255);
    analogWrite(FAN_PWM, pwm);
    Serial.print(tempC, 1);
    Serial.print(" C; PWM = "); Serial.println(pwm);
  }
}
