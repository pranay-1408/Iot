#include <LiquidCrystal.h>
const int trigPin = 3; 
const int echoPin = 2; 
const int GledPin = 12;
const int RledPin = 13;
LiquidCrystal lcd(7, 6, 5, 4, 9, 8);
const int buzzerPin = 10;
void setup() {
  // Initialize the LCD
  lcd.begin(16, 2);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(GledPin, OUTPUT);
  pinMode(RledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  noTone(buzzerPin); // Turn off the buzzer initially
}
void loop() {
  // Variables to store the duration and distance
  long duration;
  int distance;

  // Trigger the ultrasonic sensor to measure distance
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);   // Measure the echo duration
  distance = duration / 29 / 2;// Calculate the distance in centimeters

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distance: ");
  lcd.print(distance);
  lcd.print(" Cm");

  // Increase volume of the beep sensor as object gets closer
  if (distance < 100) { // Adjust this threshold as needed
    int toneFreq = map(distance, 0, 20, 200, 2000); 
    // Map distance to frequency
    tone(buzzerPin, toneFreq); // Play tone with increased frequency
    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Please STOP Now!");
  } else {
    noTone(buzzerPin); // Turn off the buzzer if no object is close
    digitalWrite(RledPin, LOW);
    digitalWrite(GledPin, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("You can Move Now");

  }
  delay(100);
}