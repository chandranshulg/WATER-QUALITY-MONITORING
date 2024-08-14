#include <ESP8266WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Wi-Fi credentials
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

// Server URL (for data posting)
const char* serverName = "http://yourserver.com/post-data";

// Sensor pins
const int phPin = A0;           // pH sensor connected to A0
const int turbidityPin = A1;    // Turbidity sensor connected to A1
const int tempPin = A2;         // Temperature sensor (optional)

// Initialize the LCD display (16x2)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Calibration constants
const float phCalibration = 3.5;     // Calibration value for pH sensor
const float turbidityCalibration = 2.0;  // Calibration value for turbidity sensor

void setup() {
  Serial.begin(9600);

  // Initialize Wi-Fi connection
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Initialize LCD display
  lcd.begin();
  lcd.backlight();
  lcd.print("Water Quality");

  delay(2000);
  lcd.clear();
}

void loop() {
  // Read sensor data
  float phValue = readPH();
  float turbidityValue = readTurbidity();
  float temperature = readTemperature();

  // Display data on LCD
  lcd.setCursor(0, 0);
  lcd.print("pH: ");
  lcd.print(phValue);

  lcd.setCursor(0, 1);
  lcd.print("Turbidity: ");
  lcd.print(turbidityValue);

  // Send data to server
  sendDataToServer(phValue, turbidityValue, temperature);

  // Delay before next reading
  delay(10000); // 10 seconds
}

// Function to read pH sensor data
float readPH() {
  int phRawValue = analogRead(phPin);
  float voltage = phRawValue * (5.0 / 1023.0);
  float phValue = -5.7 * voltage + phCalibration; // Calibration formula
  return phValue;
}

// Function to read turbidity sensor data
float readTurbidity() {
  int turbidityRawValue = analogRead(turbidityPin);
  float voltage = turbidityRawValue * (5.0 / 1023.0);
  float turbidityValue = turbidityCalibration * voltage; // Calibration formula
  return turbidityValue;
}

// Function to read temperature sensor data (optional)
float readTemperature() {
  int tempRawValue = analogRead(tempPin);
  float voltage = tempRawValue * (5.0 / 1023.0);
  float temperature = (voltage - 0.5) * 100.0; // Convert voltage to temperature
  return temperature;
}

// Function to send data to server
void sendDataToServer(float ph, float turbidity, float temperature) {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;

    // Prepare data in JSON format
    String postData = "{";
    postData += "\"ph\":" + String(ph) + ",";
    postData += "\"turbidity\":" + String(turbidity) + ",";
    postData += "\"temperature\":" + String(temperature);
    postData += "}";

    http.begin(client, serverName);
    http.addHeader("Content-Type", "application/json");

    int httpResponseCode = http.POST(postData);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }
}

// Function to display data on LCD
void updateLCD(float ph, float turbidity, float temperature) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("pH: ");
  lcd.print(ph);
  
  lcd.setCursor(0, 1);
  lcd.print("Turbidity: ");
  lcd.print(turbidity);

  lcd.setCursor(8, 1);
  lcd.print("Temp: ");
  lcd.print(temperature);
}

// Function to display data in the Serial Monitor
void displaySerialData(float ph, float turbidity, float temperature) {
  Serial.print("pH: ");
  Serial.print(ph);
  Serial.print(", Turbidity: ");
  Serial.print(turbidity);
  Serial.print(", Temp: ");
  Serial.println(temperature);
}

// Function to calibrate sensors (placeholder, implement as needed)
void calibrateSensors() {
  // Placeholder code for calibration
  // Implement specific calibration routines as per your sensor's datasheet
}

// Function to handle errors and alerts
void handleAlerts(float ph, float turbidity, float temperature) {
  if (ph < 6.5 || ph > 8.5) {
    Serial.println("Warning: pH out of range!");
    lcd.clear();
    lcd.print("pH Alert!");
    delay(2000);
  }

  if (turbidity > 5.0) {
    Serial.println("Warning: High Turbidity!");
    lcd.clear();
    lcd.print("Turbidity Alert!");
    delay(2000);
  }
}
