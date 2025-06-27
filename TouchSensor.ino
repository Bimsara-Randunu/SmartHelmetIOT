// Pin definitions
#define TOUCH1 D5       
#define TOUCH2 D6        
#define LEDPIN D1       

void setup() {
  Serial.begin(115200);

  pinMode(TOUCH1, INPUT);
  pinMode(TOUCH2, INPUT);
  pinMode(LEDPIN, OUTPUT);
}

void loop() {
  int touch1 = digitalRead(TOUCH1);
  int touch2 = digitalRead(TOUCH2);

  // if both sensor 1 the helmet is on
  String helmetStatus = (touch1 == 1 && touch2 == 1) ? "on" : "off";

  // LED Control
  if (helmetStatus == "on") {
    digitalWrite(LEDPIN, HIGH);
  } else {
    digitalWrite(LEDPIN, LOW);
  }

  // Serial Output
  Serial.println("---------- HELMET DETECTION ----------");
  Serial.print("Touch Sensor 1: "); Serial.println(touch1);
  Serial.print("Touch Sensor 2: "); Serial.println(touch2);
  Serial.print("Helmet Status: "); Serial.println(helmetStatus);
  Serial.println("--------------------------------------");

  delay(1000);  // Update every second
}
