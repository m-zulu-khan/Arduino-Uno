// Define the pin for the PIR sensor
int pirPin = 2;
int pirState = LOW; // Default state is LOW (no motion detected)

void setup() {
  pinMode(pirPin, INPUT);  // Set the PIR pin as input
  Serial.begin(9600);  // Initialize the serial monitor
}

void loop() {
  int val = digitalRead(pirPin);  // Read the PIR sensor value

  if (val == HIGH) {  // If motion is detected
    if (pirState == LOW) {
      Serial.println("Motion detected!");
      pirState = HIGH;  // Update state to motion detected
    }
  } else {
    if (pirState == HIGH) {
      Serial.println("Motion ended!");
      pirState = LOW;  // Update state to no motion
    }
  }
}
