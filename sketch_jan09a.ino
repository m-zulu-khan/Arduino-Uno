int IRSensor = 9; // connect IR sensor module to Arduino pin 9
int LED = 13; // connect LED to Arduino pin 13

void setup()
{
  Serial.begin(9600); // Initialize Serial at 9600 Baud
  Serial.println("Serial Working"); // Test to check if serial is working or not
  pinMode(IRSensor, INPUT); // IR Sensor pin INPUT
  pinMode(LED, OUTPUT); // LED Pin Output
}

void loop()
{
  int sensorStatus = digitalRead(IRSensor); // Set the GPIO as Input
  if (sensorStatus == 1) // Check if the pin is high or not
  {
    // if the pin is high, turn off the onboard LED
    digitalWrite(LED, LOW); // LED LOW
    Serial.println("Motion Ended!"); // print "Motion Ended!" on the serial monitor window
  }
  else
  {
    // if the pin is low, turn on the onboard LED
    digitalWrite(LED, HIGH); // LED HIGH
    Serial.println("Motion Detected!"); // print "Motion Detected!" on the serial monitor window
  }
}
