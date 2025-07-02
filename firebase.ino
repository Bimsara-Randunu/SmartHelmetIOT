#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <DHT.h>

// Wi-Fi credentials
#define WIFI_SSID "SRINATH"
#define WIFI_PASSWORD "12345678"

// Firebase credentials
#define API_KEY "AIzaSyArlbHhgGqpyRqo_aHceHs071OtSNtHK-w"
#define DATABASE_URL "https://smarthelmet-a1b6f-default-rtdb.asia-southeast1.firebasedatabase.app"

// Firebase Auth credentials
#define USER_EMAIL "bimsararandunu9899@gmail.com"
#define USER_PASSWORD "Bimsara12345"

// Pin definitions
#define DHTPIN D2
#define DHTTYPE DHT22
#define TOUCH1 D5
#define TOUCH2 D6
#define VIBRATION_PIN D3
#define LEDPIN D1
#define BUZZER_PIN D8
#define GAS_SENSOR A0

// Firebase objects
FirebaseData firebaseData;
FirebaseAuth auth;
FirebaseConfig config;

// DHT sensor
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();

  pinMode(TOUCH1, INPUT);
  pinMode(TOUCH2, INPUT);
  pinMode(VIBRATION_PIN, INPUT);
  pinMode(LEDPIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Wi-Fi
  Serial.print("Connecting to Wi-Fi");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n Wi-Fi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Firebase
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {
  float temp = dht.readTemperature();
  float humidity = dht.readHumidity();
  int gasValue = analogRead(GAS_SENSOR);
  int touch1 = digitalRead(TOUCH1);
  int touch2 = digitalRead(TOUCH2);
  int vibration = digitalRead(VIBRATION_PIN);  

  String helmetStatus = (touch1 == 1 && touch2 == 1) ? "on" : "off";
  String emergencyStatus = (vibration == HIGH) ? "on" : "off";

  // LED & Buzzer control
  if (temp >= 25 || humidity >= 60  || emergencyStatus == "on") {
    digitalWrite(LEDPIN, HIGH);//red
    digitalWrite(BUZZER_PIN, HIGH);
  } else {
    digitalWrite(LEDPIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
  }

  // Serial Monitor Output
  Serial.println("--------- SENSOR READINGS ---------");
  Serial.print("Temperature: "); Serial.println(temp);
  Serial.print("Humidity: "); Serial.println(humidity);
  Serial.print("Gas Value: "); Serial.println(gasValue);
  Serial.print("Touch 1: "); Serial.println(touch1);
  Serial.print("Touch 2: "); Serial.println(touch2);
  Serial.print("Helmet Status: "); Serial.println(helmetStatus);
  Serial.print("Vibration: "); Serial.println((vibration == LOW) ? "Detected" : "None");
  Serial.print("Emergency Status: "); Serial.println(emergencyStatus);
  Serial.println("-----------------------------------");

  // Firebase Upload
  Firebase.setFloat(firebaseData, "/helmetData/temperature", temp);
  Firebase.setFloat(firebaseData, "/helmetData/humidity", humidity);
  Firebase.setInt(firebaseData, "/helmetData/gas", gasValue);
  Firebase.setString(firebaseData, "/helmetData/helmetStatus", helmetStatus);
  Firebase.setString(firebaseData, "/helmetData/emergencyStatus", emergencyStatus);

  delay(3000);  
}

