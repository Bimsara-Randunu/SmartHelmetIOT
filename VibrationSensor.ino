#include <DHT.h>

// Pin definitions
#define VIBRATION_PIN D3     // SW-420 digital output
#define LEDPIN D1            // LED
#define BUZZER_PIN D8        // Buzzer (optional)
#define DHTPIN D2
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);  // Optional: still initialize in case of future use

void setup() {
  Serial.begin(115200);
  dht.begin();  // Optional init

  pinMode(VIBRATION_PIN, INPUT);
  pinMode(LEDPIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  int vibrationState = digitalRead(VIBRATION_PIN);  // LOW = vibration detected

  Serial.println(" VIBRATION CHECK ");
  Serial.print("Vibration Status: ");
  Serial.println(vibrationState == LOW ? "DETECTED" : "NONE");

  if (vibrationState == LOW) {
    digitalWrite(LEDPIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
  } else {
    digitalWrite(LEDPIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
  }

  delay(500);  // Check every 0.5 seconds
}
