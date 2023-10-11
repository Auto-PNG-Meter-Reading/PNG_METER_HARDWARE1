const int REED_PIN = 2;    // Pin connected to reed switch
const int LED_PIN = 13;    // LED pin
int ledHighCount = 0;       // Variable to count LED HIGH state
int previousLedState = LOW; // Variable to store the previous state of the LED

void setup() {
  Serial.begin(9600);
  pinMode(REED_PIN, INPUT_PULLUP);    // Enable internal pull-up for the reed switch
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  int proximity = digitalRead(REED_PIN); // Read the state of the switch
  int ledState = digitalRead(LED_PIN);   // Read the state of the LED

  // If the pin reads low, the switch is closed.
  if (proximity == LOW) {
    Serial.println("Switch closed");
    digitalWrite(LED_PIN, HIGH);    // Turn the LED on
  }
  else {
    Serial.println("Switch opened");
    digitalWrite(LED_PIN, LOW);      // Turn the LED off
  }

  // Check if the LED has transitioned from LOW to HIGH
  if (ledState == HIGH && previousLedState == LOW) {
    ledHighCount++;
  }

  // Store the current LED state for the next iteration
  previousLedState = ledState;

  // Print the LED HIGH count to the serial monitor
  Serial.print("LED HIGH count: ");
  Serial.println(ledHighCount);

  delay(1000); // You can adjust this delay to control the rate of counting
}
