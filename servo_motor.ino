#include <Servo.h>

Servo myServo; // Create a servo object
int pos = 0;   // Variable to store the servo position

void setup() {
  myServo.attach(2); // Attach the servo to pin 9
}

void loop() {
  // Move from 0 to 180 degrees
  for (pos = 0; pos <= 180; pos += 1) {
    myServo.write(pos);  // Tell servo to go to position in variable 'pos'
    delay(15);           // Wait 15 ms for the servo to reach the position
  }
  delay(1000); // Wait for 1 second at 180 degrees

  // Move from 180 to 0 degrees
  for (pos = 180; pos >= 0; pos -= 1) {
    myServo.write(pos);  // Tell servo to go to position in variable 'pos'
    delay(15);           // Wait 15 ms for the servo to reach the position
  }
  delay(1000); // Wait for 1 second at 0 degrees
}
