void setup() {
  // Initialize the LED pin as an output:
  pinMode(2, OUTPUT);
}

void loop() {
  // Turn the LED on (HIGH is the voltage level):
  digitalWrite(2, HIGH);
  delay(1000); // Wait for a second

  // Turn the LED off by making the voltage LOW:
  digitalWrite(2, LOW);
  delay(1000); // Wait for a second
}
