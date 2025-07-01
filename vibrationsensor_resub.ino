#include <DHT.h>

// Pin definitions
#define VIBRATION_PIN D3     
#define LEDPIN D1            
#define BUZZER_PIN D8        
#define DHTPIN D2
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE); 

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
  Serial.println(vibrationState == HIGH ? "DETECTED" : "NONE");

  if (vibrationState == HIGH) {
    digitalWrite(LEDPIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
  } else {
    digitalWrite(LEDPIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
  }

  delay(500);  
}
