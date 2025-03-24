const int buttonPin1 = 8;  // First push button connected to digital pin 8
const int buttonPin2 = 9;  // Second push button connected to digital pin 9
const int buttonPin3 = 10; // Third push button connected to digital pin 10
const int relayPin = 13;   // Relay connected to digital pin 13

void setup() {
  pinMode(buttonPin1, INPUT_PULLUP); // Set the button pin as an input with internal pull-up resistor
  pinMode(buttonPin2, INPUT_PULLUP); // Set the button pin as an input with internal pull-up resistor
  pinMode(buttonPin3, INPUT_PULLUP); // Set the button pin as an input with internal pull-up resistor
  pinMode(relayPin, OUTPUT);         // Set the relay pin as an output
  //digitalWrite(relayPin, LOW);   ]
  // Initialize the relay in low mode
  Serial.begin(9600);
}

void loop() {
  
   digitalWrite(relayPin, HIGH);
   Serial.println("high");// Turn on the relay
    delay(10000);                 // Keep the relay on for 10 seconds
    digitalWrite(relayPin, LOW); 
    Serial.println("low");
     delay(10000);   

  
}
