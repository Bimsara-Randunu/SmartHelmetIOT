// Pin definitions
#define GAS_SENSOR A0       // MQ-135 analog output
#define LEDPIN D1           // LED pin
#define BUZZER_PIN D8       // Buzzer pin (optional)

void setup() {
  Serial.begin(115200);

  pinMode(GAS_SENSOR, INPUT);
  pinMode(LEDPIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  int gasValue = analogRead(GAS_SENSOR);  // Read analog gas value (0–1023)

  Serial.println("---------- AIR QUALITY CHECK ----------");
  Serial.print("Gas Sensor Value: ");
  Serial.println(gasValue);

  // If gas value exceeds threshold, activate buzzer and LED
  if (gasValue > 30) {
    digitalWrite(LEDPIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
  } else {
    digitalWrite(LEDPIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
  }

  delay(2000);  // Read every 2 seconds
}
