// Define segment pins for a Common Anode 7-segment display
const int a = 2;
const int b = 3;
const int c = 4;
const int d = 5;
const int e = 6;
const int f = 7;
const int g = 8;
const int dp = 9;  // Decimal point (not used in this example)

// Array to store segment control for digits 0-9
const int digits[10][7] = {
  {LOW, LOW, LOW, LOW, LOW, LOW, HIGH}, // 0
  {HIGH, LOW, LOW, HIGH, HIGH, HIGH, HIGH}, // 1
  {LOW, LOW, HIGH, LOW, LOW, HIGH, LOW}, // 2
  {LOW, LOW, LOW, LOW, HIGH, HIGH, LOW}, // 3
  {HIGH, LOW, LOW, HIGH, HIGH, LOW, LOW}, // 4
  {LOW, HIGH, LOW, LOW, HIGH, LOW, LOW}, // 5
  {LOW, HIGH, LOW, LOW, LOW, LOW, LOW}, // 6
  {LOW, LOW, LOW, HIGH, HIGH, HIGH, HIGH}, // 7
  {LOW, LOW, LOW, LOW, LOW, LOW, LOW}, // 8
  {LOW, LOW, LOW, LOW, HIGH, LOW, LOW}  // 9
};

// Function to display a digit on the 7-segment display
void displayDigit(int digit) {
  digitalWrite(a, digits[digit][0]);
  digitalWrite(b, digits[digit][1]);
  digitalWrite(c, digits[digit][2]);
  digitalWrite(d, digits[digit][3]);
  digitalWrite(e, digits[digit][4]);
  digitalWrite(f, digits[digit][5]);
  digitalWrite(g, digits[digit][6]);
}

void setup() {
  // Set segment pins as outputs
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(dp, OUTPUT);

  // Initialize all segments to OFF
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(dp, HIGH);
}

void loop() {
  // Loop through digits 0-9
  for (int i = 0; i < 10; i++) {
    displayDigit(i);
    delay(5000);  // Display each digit for 1 second
  }
}
