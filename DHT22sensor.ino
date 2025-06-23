#include <DHT.h>

// Pin definitions
#define DHTPIN D2
#define DHTTYPE DHT22
#define LEDPIN D1
#define BUZZER_PIN D8  // 

// DHT sensor object
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();

  pinMode(LEDPIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  float temp = dht.readTemperature();   //  temperature in °C
  float humidity = dht.readHumidity();  //  humidity in %

  Serial.println(" SENSOR DATA ");
  Serial.print("Temperature: "); Serial.print(temp); Serial.println(" °C");
  Serial.print("Humidity: "); Serial.print(humidity); Serial.println(" %");
 

  // If temperature or humidity exceeds threshold,on LED and buzzer
  if (temp >= 25 || humidity >= 60) {
    digitalWrite(LEDPIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
  } else {
    digitalWrite(LEDPIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
  }

  delay(5000);  // Wait for 5 seconds
}
