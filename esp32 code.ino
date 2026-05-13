#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <DHT.h>

// ---------------- PINS ----------------
#define FLAME_PIN 33
#define MQ135_PIN 34
#define SOUND_PIN 35
#define WATER_PIN 32
#define VIBRATION_PIN 23   

#define BUZZER_MAIN 25     
#define BUZZER_WATER 27     
#define BUZZER_VIB 14       

#define SOUND_LED 26
#define TEMP_LED 13

// ---------------- DHT ----------------
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// ---------------- WIFI ----------------
const char* ssid = "ONE PLUS MAAZ";
const char* password = "maazmk02";

// ---------------- FIREBASE ----------------
String firebaseHost = "https://smart-industrial-safety-d5554-default-rtdb.asia-southeast1.firebasedatabase.app";

// ---------------- THRESHOLDS ----------------
int gasThreshold = 600;
int soundThreshold = 1020;
float tempLimit = 35.0;
float humLimit = 80.0;

void setup() {
  Serial.begin(115200);

  pinMode(FLAME_PIN, INPUT);
  pinMode(WATER_PIN, INPUT);
  pinMode(VIBRATION_PIN, INPUT);

  pinMode(BUZZER_MAIN, OUTPUT);
  pinMode(BUZZER_WATER, OUTPUT);
  pinMode(BUZZER_VIB, OUTPUT);

  pinMode(SOUND_LED, OUTPUT);
  pinMode(TEMP_LED, OUTPUT);

  dht.begin();

  WiFi.begin(ssid, password);
  Serial.print("Connecting WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\n✅ WiFi Connected");
}

void loop() {

  // ---------------- READ SENSORS ----------------
  int flame = digitalRead(FLAME_PIN);
  int gasValue = analogRead(MQ135_PIN);
  int soundValue = analogRead(SOUND_PIN);
  int vibState = digitalRead(VIBRATION_PIN);
  int waterState = digitalRead(WATER_PIN);

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("❌ DHT ERROR");
    delay(2000);
    return;
  }

  // ---------------- CONDITIONS ----------------
  bool fireDetected = (flame == LOW);
  bool gasDetected = (gasValue > gasThreshold);
  bool soundDetected = (soundValue > soundThreshold);
  bool vibDetected = (vibState == LOW);
  bool tempAlert = (temperature > tempLimit || humidity > humLimit);
  bool tankFull = (waterState == HIGH);

  // ---------------- BUZZERS ----------------
  digitalWrite(BUZZER_MAIN, (fireDetected || gasDetected));
  digitalWrite(BUZZER_WATER, tankFull);
  digitalWrite(BUZZER_VIB, vibDetected);

  // ---------------- LED ----------------
  digitalWrite(SOUND_LED, soundDetected);
  digitalWrite(TEMP_LED, tempAlert);

  // ---------------- SERIAL ----------------
  Serial.println("\n----- SYSTEM STATUS -----");
  Serial.println("Gas: " + String(gasValue));
  Serial.println("Sound: " + String(soundValue));
  Serial.println("Vibration: " + String(vibState));
  Serial.println("Temp: " + String(temperature));
  Serial.println("Humidity: " + String(humidity));
  Serial.println("Water: " + String(waterState));

  // ---------------- FIREBASE ----------------
  if (WiFi.status() == WL_CONNECTED) {

    WiFiClientSecure client;
    client.setInsecure();  // 🔓 VERY IMPORTANT

    HTTPClient http;
    String url = firebaseHost + "/sensor.json";

    http.begin(client, url);   // ✅ FIXED
    http.addHeader("Content-Type", "application/json");

    String json = "{";
    json += "\"fire\":\"" + String(fireDetected ? "FIRE DETECTED" : "SAFE") + "\",";
    json += "\"gas\":{\"value\":" + String(gasValue) + ",\"status\":\"" + String(gasDetected ? "GAS DETECTED" : "SAFE") + "\"},";
    json += "\"sound\":{\"value\":" + String(soundValue) + ",\"status\":\"" + String(soundDetected ? "HIGH" : "NORMAL") + "\"},";
    json += "\"vibration\":{\"value\":" + String(vibState) + ",\"status\":\"" + String(vibDetected ? "DETECTED" : "NORMAL") + "\"},";
    json += "\"temperature\":" + String(temperature) + ",";
    json += "\"humidity\":" + String(humidity) + ",";
    json += "\"water\":\"" + String(tankFull ? "FULL" : "EMPTY") + "\"";
    json += "}";

    Serial.println("Sending JSON:");
    Serial.println(json);

    int response = http.PUT(json);

    Serial.print("Firebase Response: ");
    Serial.println(response);

    if (response > 0) {
      Serial.println(http.getString());
    }

    http.end();
  }

  delay(2000);
}