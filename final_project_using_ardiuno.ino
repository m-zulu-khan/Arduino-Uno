#include <LiquidCrystal.h>

// Initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int hoursButton = 8;
const int minusButton = 9;
const int startButton = 10;
const int relayPin = 13;

int seconds = 59;
int minutes = 0;
int hour = 0;

void setup() {
  lcd.begin(16, 2); // Set up the LCD's number of columns and rows
  lcd.print("Digital socket:");
  pinMode(hoursButton, INPUT_PULLUP);
  pinMode(minusButton, INPUT_PULLUP);
  pinMode(startButton, INPUT_PULLUP);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH); // Set relay to low mode on initialization

  Serial.begin(9600); // Initialize Serial Monitor
  displayTime();
}

void loop() {
  setTime();
}

void delayMs(unsigned int ms) {
  delay(ms);
}

void displayTime() {
  lcd.setCursor(0, 1);
  if (hour < 10) lcd.print("0");
  lcd.print(hour);
  lcd.print(":");
  if (minutes < 10) lcd.print("0");
  lcd.print(minutes);
  lcd.print(":");
  if (seconds < 10) lcd.print("0");
  lcd.print(seconds);
}

void decrementHour() {
  hour--;
  if (hour <= 0) {
    digitalWrite(relayPin, HIGH);
    while (1) {
      lcd.setCursor(0, 1);
      lcd.print("Times Up        ");
    }
  }
}

void decrementMinutes() {
  minutes--;
  if (minutes <= 0) {
    minutes = 59;
    decrementHour();
  }
}

void decrementTime() {
  seconds--;
  if (seconds <= 0) {
    seconds = 59;
    decrementMinutes();
  }
  displayTime();
  delayMs(1000);
}

void startTimer() {
  digitalWrite(relayPin, LOW); // Activate relay when timer starts
  while (1) {
    decrementTime();
  }
}

void setTime() {
  if (digitalRead(hoursButton) == LOW) {
    hour++;
    if (hour > 5) {
      hour = 0;
    }
    displayTime();
    Serial.print("Hour: ");
    Serial.println(hour);
    delayMs(1000);
  }

  if (digitalRead(minusButton) == LOW) {
    minutes++;
    if (minutes > 59) {
      minutes = 0;
    }
    displayTime();
    Serial.print("Minutes: ");
    Serial.println(minutes);
    delayMs(1000);
  }

  if (digitalRead(startButton) == LOW) {
    startTimer();
  }
}
