#include <Servo.h> 
Servo baseServo; 
const int joy1X = A0; 
int baseServoPin=9;
int baseAngle;

void setup() {  
  baseServo.attach(baseServoPin);
    baseServo.write(90);
    Serial.begin(9600);
  }

void loop() { 
  // Read joystick position
  int joy1XPos = analogRead(joy1X);
   //delay(1000);
  // Map joystick position to servo angle (0 to 180 degrees)
   if (joy1XPos <= 300 || joy1XPos >= 800){
  int baseAngle = map(joy1XPos, 0, 1023, 0, 160);
  baseServo.write(baseAngle);
// Serial.write(baseServo);
  }
   delay(1000);
    // Write the angle to the base servo
  
   
    
   
   
}
