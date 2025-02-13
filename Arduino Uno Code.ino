#include <DHT.h>
#include <Wire.h>

// Pin Definitions
#define TRIG1 6
#define ECHO1 7
#define TRIG2 8
#define ECHO2 9
#define PIR_PIN 3
#define DHT_PIN 2
#define BUZZER_PIN 5

// DHT Sensor Type
#define DHT_TYPE DHT11
DHT dht(DHT_PIN, DHT_TYPE);

// Variables
int peopleCount = 0;
float distance1, distance2;
float threshold = 20.0; // cm threshold for detecting a person
unsigned long roomStartTime = 0;
bool roomOccupied = false;

// Function to get distance from ultrasonic sensor
float getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 25000); // Timeout after 25ms
  if (duration == 0) return 500; // Return a large value if no echo
  return (duration * 0.034) / 2; // Convert to cm
}

void setup() {
  // Serial Communication
  Serial.begin(9600);

  // Ultrasonic Sensor Pins
  pinMode(TRIG1, OUTPUT);
  pinMode(ECHO1, INPUT);
  pinMode(TRIG2, OUTPUT);
  pinMode(ECHO2, INPUT);

  // PIR Sensor and Buzzer Pins
  pinMode(PIR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Initialize DHT sensor
  dht.begin();

  // Welcome Message
  Serial.println("Smart Room Initialized");
  delay(2000);
}

void loop() {
  // Measure distances from both sensors
  distance1 = getDistance(TRIG1, ECHO1);
  distance2 = getDistance(TRIG2, ECHO2);

  // Entry Logic: US1 triggered before US2
  if (distance1 < threshold && distance2 > threshold) {
    delay(200); // Debounce delay
    distance2 = getDistance(TRIG2, ECHO2);
    if (distance2 < threshold) {
      peopleCount++;
      Serial.println("Entry detected");
      Serial.print("People count: ");
      Serial.println(peopleCount);
      roomOccupied = true;
      if (peopleCount == 1) {
        roomStartTime = millis(); // Start timing occupancy
      }
      delay(1000); // Avoid double counting
    }
  }

  // Exit Logic: US2 triggered before US1
  if (distance2 < threshold && distance1 > threshold) {
    delay(200); // Debounce delay
    distance1 = getDistance(TRIG1, ECHO1);
    if (distance1 < threshold) {
      if (peopleCount > 0) {
        peopleCount--;
        Serial.println("Exit detected");
        Serial.print("People count: ");
        Serial.println(peopleCount);
        if (peopleCount == 0) {
          roomOccupied = false;
        }
        delay(1000); // Avoid double counting
      }
    }
  }

  // Read Temperature and Humidity
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Check for valid readings
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("DHT sensor error");
    return;
  }

  // Update buzzer status based on room occupancy
  if (roomOccupied) {
    digitalWrite(BUZZER_PIN, HIGH); // Turn on buzzer
  } else {
    digitalWrite(BUZZER_PIN, LOW); // Turn off buzzer
  }

  // Calculate and log time occupied
  unsigned long timeOccupied = roomOccupied ? (millis() - roomStartTime) / 1000 : 0;

  // Send Data to Serial Monitor
  Serial.print("Room: ");
  Serial.print(roomOccupied ? "Occupied" : "Vacant");
  Serial.print(", People: ");
  Serial.print(peopleCount);
  Serial.print(", Temp: ");
  Serial.print(temperature, 1);
  Serial.print("C, Humidity: ");
  Serial.print(humidity, 1);
  Serial.print("%, Time Occupied: ");
  Serial.print(timeOccupied);
  Serial.println(" seconds");

  delay(500); // Update every 500ms
}