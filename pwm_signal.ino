void setup() {
  pinMode(9, OUTPUT);
  // Set pin 9 as an output
  Serial.begin(9600);
}

void loop() {
  analogWrite(9, 100);
/*  // Increase brightness
  for (int brightness = 0; brightness <= 255; brightness++) {
    analogWrite(9, brightness);  // Write the brightness value to pin 9
    delay(100);  // Wait for 10 milliseconds to see the change
    Serial.println(brightness);
  
  }
  // Decrease brightness
  for (int brightness = 255; brightness >= 0; brightness--) {
    analogWrite(9, brightness);  // Write the brightness value to pin 9
    delay(10);  // Wait for 10 milliseconds to see the change
    Serial.println(brightness);
  }*/
}
