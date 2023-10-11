const int REED_PIN = D4;    // Pin connected to reed switch
const int LED_PIN = D0;    // LED pin
int ledHighCount = 0;       // Variable to count LED HIGH state

void setup() {
  Serial.begin(9600);
  pinMode(REED_PIN, INPUT_PULLUP);    // Enable internal pull-up for the reed switch
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  int proximity = digitalRead(REED_PIN); // Read the state of the switch
  
  // If the pin reads low, the switch is closed.
  if (proximity == LOW) {
    Serial.println("Switch closed");
    digitalWrite(LED_PIN, HIGH);    // Turn the LED on
    ledHighCount++;                 // Increment the LED HIGH count
  }
  else {
    Serial.println("Switch opened");
    digitalWrite(LED_PIN, LOW);      // Turn the LED off
  }

  // Print the LED HIGH count to the serial monitor
  Serial.print("LED HIGH count: ");
  Serial.println(ledHighCount);

  delay(500); // You can adjust this delay to control the rate of counting
}
