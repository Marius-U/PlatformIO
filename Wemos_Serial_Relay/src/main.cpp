/*
 * Control an Relay from a web browser
 * Build to be run on an ESP8266
 * 
 * connect to the ESP8266 AP then
 * use web broswer to go to 192.168.4.1
 * 
 */
 
 
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>        // Include the mDNS library

#define POWER D1
#define BM0   D2
#define BM1   D3
#define BM2   D4

#define COMMAND D8
#define RESET   D7

char serial = 0;
int buttonStateC;             // the current reading from the input pin
int buttonStateR;             // the current reading from the input pin
int lastButtonStateC = LOW;   // the previous reading from the input pin
int lastButtonStateR = LOW;   // the previous reading from the input pin

int readingC = 0;
int readingR = 0;

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTimeC = 0;  // the last time the output pin was toggled
unsigned long lastDebounceTimeR = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
unsigned int count = 0;

void setup() 
{
  Serial.begin(115200);
  delay(10);
  Serial.println('\n');

  pinMode(POWER, OUTPUT); 
  pinMode(BM0, OUTPUT); 
  pinMode(BM1, OUTPUT); 
  pinMode(BM2, OUTPUT); 
  pinMode(COMMAND, INPUT);
  pinMode(RESET, INPUT);

  digitalWrite(POWER, HIGH);
  digitalWrite(BM0, HIGH);
  digitalWrite(BM1, HIGH);
  digitalWrite(BM2, HIGH);

  digitalWrite(COMMAND, LOW);
  digitalWrite(RESET, LOW);

  Serial.println("INIT Done!");

} 



void doSerialJob()
{
  if (Serial.available())
  {
    serial = Serial.read();
    
  }
  if(serial== 'b')
  {
    digitalWrite(POWER, HIGH);
    delay(500);
    digitalWrite(BM0, LOW);
    digitalWrite(BM1, LOW);
    digitalWrite(BM2, LOW);
    delay(10);
    digitalWrite(POWER, LOW);
    count++;
  }
  else if(serial == 'r')
  {
    digitalWrite(POWER, HIGH);
    delay(500);
    digitalWrite(BM0, HIGH);
    digitalWrite(BM1, HIGH);
    digitalWrite(BM2, HIGH);
    delay(10);
    digitalWrite(POWER, LOW); 
    count++;
  }
  else if(serial == 's')
  {
    digitalWrite(POWER, HIGH);
    digitalWrite(BM0, HIGH);
    digitalWrite(BM1, HIGH);
    digitalWrite(BM2, HIGH);
    count = 0;
  }
  else
  {
        serial = 0;
  }
  serial = 0;
}
void debounceButtonCommand()
{
  // read the state of the switch into a local variable:
  readingC = digitalRead(COMMAND);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (readingC != lastButtonStateC) {
    // reset the debouncing timer
    lastDebounceTimeC = millis();
  }

  if ((millis() - lastDebounceTimeC) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (readingC != buttonStateC) {
      buttonStateC = readingC;

      // only do action if the new button state is HIGH
      if (buttonStateC == HIGH) {
        if((count & 0x01) == 0x00)
        {
           serial = 'r';
        }
        else
        {
           serial = 'b';
        }
      }
    }
  }
  lastButtonStateC = readingC;
}
void debounceButtonReset()
{
    // read the state of the switch into a local variable:
  readingR = digitalRead(RESET);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (readingR != lastButtonStateR) {
    // reset the debouncing timer
    lastDebounceTimeR = millis();
  }

  if ((millis() - lastDebounceTimeR) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (readingR != buttonStateR) {
      buttonStateR = readingR;

      // only do action if the new button state is HIGH
      if (buttonStateR == HIGH) {
        digitalWrite(POWER, HIGH);
        digitalWrite(BM0, HIGH);
        digitalWrite(BM1, HIGH);
        digitalWrite(BM2, HIGH);
        serial = 0;
        count = 0;
      }
    }
  }
  lastButtonStateR = readingR;
}
void loop() 
{
  debounceButtonCommand();
  debounceButtonReset();
  doSerialJob();
  
}