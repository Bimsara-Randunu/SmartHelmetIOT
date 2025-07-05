#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <DHT.h>

// Wi-Fi credentials
#define WIFI_SSID ";-)"
#define WIFI_PASSWORD "cxfu4394"

// Firebase credentials
#define API_KEY "AIzaSyArlbHhgGqpyRqo_aHceHs071OtSNtHK-w"
#define DATABASE_URL "https://smarthelmet-a1b6f-default-rtdb.asia-southeast1.firebasedatabase.app"

// Firebase auth credentials
#define USER_EMAIL "bimsararandunu9899@gmail.com"
#define USER_PASSWORD "Bimsara12345"

// Pin definitions
#define DHTPIN D2
#define DHTTYPE DHT22
#define TOUCH1 D5
#define TOUCH2 D8
#define GREEN_LED D1         
#define RED_LED D7           
#define GAS_SENSOR A0
#define VIBRATION_PIN D3
#define BUTTON_PIN D6        
#define BUZZER_PIN D0        

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
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GAS_SENSOR, INPUT);
  pinMode(VIBRATION_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);   
  pinMode(BUZZER_PIN, OUTPUT);         
  digitalWrite(BUZZER_PIN, LOW);       

  // Connect to Wi-Fi
  Serial.print("Connecting to Wi-Fi");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n Wi-Fi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Configure Firebase
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
  int vibrationState = digitalRead(VIBRATION_PIN);  // LOW = detected
  int buttonState = digitalRead(BUTTON_PIN);        // LOW = pressed

  // Helmet Status
  String helmetStatus = (touch1 == 1 && touch2 == 1) ? "on" : "off";

  // Vibration and Emergency
  String vibrationStatus = (vibrationState == LOW) ? "on" : "off";
  String emergencyStatus = (buttonState == LOW) ? "on" : "off";

  // LED & Buzzer Control
  bool redLedState = (temp >= 35 || humidity >= 90);

  digitalWrite(RED_LED, redLedState ? HIGH : LOW);
  digitalWrite(BUZZER_PIN, redLedState ? HIGH : LOW);   // Buzzer ON when red LED ON
  digitalWrite(GREEN_LED, helmetStatus == "on" ? HIGH : LOW);

  // Serial Monitor Output
  Serial.println("========== SMART HELMET ==========");
  Serial.print("Temperature: "); Serial.println(temp);
  Serial.print("Humidity: "); Serial.println(humidity);
  Serial.print("Gas: "); Serial.println(gasValue);
  Serial.print("Helmet Status: "); Serial.println(helmetStatus);
  Serial.print("Vibration Status: "); Serial.println(vibrationStatus);
  Serial.print("Emergency Button: "); Serial.println(buttonState == LOW ? "PRESSED" : "RELEASED");
  Serial.print("Emergency Status: "); Serial.println(emergencyStatus);
  Serial.print("Red LED: "); Serial.println(redLedState ? "ON" : "OFF");
  Serial.print("Buzzer: "); Serial.println(redLedState ? "ON" : "OFF");
  Serial.println("===================================");

  // Firebase Upload
  if (!Firebase.setFloat(firebaseData, "/helmetData/temperature", temp))
    Serial.println(" Temp upload failed: " + firebaseData.errorReason());

  if (!Firebase.setFloat(firebaseData, "/helmetData/humidity", humidity))
    Serial.println(" Humidity upload failed: " + firebaseData.errorReason());

  if (!Firebase.setInt(firebaseData, "/helmetData/gas", gasValue))
    Serial.println(" Gas upload failed: " + firebaseData.errorReason());

  if (!Firebase.setString(firebaseData, "/helmetData/helmetStatus", helmetStatus))
    Serial.println(" Helmet status upload failed: " + firebaseData.errorReason());

  if (!Firebase.setString(firebaseData, "/helmetData/vibrationStatus", vibrationStatus))
    Serial.println(" Vibration status upload failed: " + firebaseData.errorReason());

  if (!Firebase.setString(firebaseData, "/helmetData/emergencyStatus", emergencyStatus))
    Serial.println(" Emergency status upload failed: " + firebaseData.errorReason());

  delay(1000);  // 1-second loop
}
