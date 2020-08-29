#include <Arduino.h>
/*
void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
}

*/

void setup() {
  // initialize digital pin 10 as an output.
  pinMode(10, OUTPUT);
}
 
// the loop function runs over and over again forever
void loop() {
  digitalWrite(10, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(10, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}