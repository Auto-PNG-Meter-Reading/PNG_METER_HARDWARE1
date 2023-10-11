#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "Ankitkg";        // Replace with your WiFi network SSID
const char* password = "1209876543"; // Replace with your WiFi password
const char* serverAddress = "http://localhost:8080/Example-1/nodeserver.html"; // Replace with your server address

const int REED_PIN = D4;    // Pin connected to reed switch
const int LED_PIN = D0;    // LED pin
int ledHighCount = 0;       // Variable to count LED HIGH state

// Create a WiFiClient object to use for HTTP requests
WiFiClient client;

void setup() {
  Serial.begin(9600);
  pinMode(REED_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  int proximity = digitalRead(REED_PIN);

  if (proximity == LOW) {
    Serial.println("Switch closed");
    digitalWrite(LED_PIN, HIGH);
    ledHighCount++;
  }
  else {
    Serial.println("Switch opened");
    digitalWrite(LED_PIN, LOW);
  }

  Serial.print("LED HIGH count: ");
  Serial.println(ledHighCount);

  // Send data to the web server
  sendToServer(proximity, ledHighCount);

  delay(1000);
}

void sendToServer(int proximity, int ledCount) {
  HTTPClient http;

  // Construct the URL with query parameters to send data to your server
  String url = String(serverAddress) + "?proximity=" + String(proximity) + "&ledCount=" + String(ledCount);

  // Start the HTTP request
  http.begin(client, url);

  // Send the request
  int httpCode = http.GET();

  if (httpCode == HTTP_CODE_OK) {
    Serial.println("Data sent successfully");
  } else {
    Serial.println("Data send failed");
  }

  http.end();
}