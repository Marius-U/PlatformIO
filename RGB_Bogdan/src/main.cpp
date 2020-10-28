#include <Arduino.h>

#define B_LED  D5
#define R_LED  D6
#define G_LED  D7

void setup() {

  pinMode(B_LED, OUTPUT);
  pinMode(R_LED, OUTPUT);
  pinMode(G_LED, OUTPUT);

  digitalWrite(B_LED, LOW);
  digitalWrite(R_LED, LOW);
  digitalWrite(G_LED, LOW);

  Serial.begin(9600);
}

void loop() 
{
 /* digitalWrite(B_LED, LOW);
  digitalWrite(R_LED, LOW);
  digitalWrite(G_LED, LOW);
  Serial.println("LOW");
  delay(2000);*/
  digitalWrite(B_LED, HIGH);
  digitalWrite(R_LED, HIGH);
  digitalWrite(G_LED, HIGH);
  Serial.println("HIGH");
  /*delay(2000);
  digitalWrite(B_LED, HIGH);
  digitalWrite(R_LED, LOW);
  digitalWrite(G_LED, LOW);
  Serial.println("BLUE");
  delay(2000);
  digitalWrite(B_LED, LOW);
  digitalWrite(R_LED, HIGH);
  digitalWrite(G_LED, LOW);
  Serial.println("RED");
  delay(2000);
  digitalWrite(B_LED, LOW);
  digitalWrite(R_LED, LOW);
  digitalWrite(G_LED, HIGH);
  Serial.println("GREEN");
  delay(2000);*/
}