#include <Arduino.h>

#define encoder0PinA  2
#define encoder0PinB  3

void ICACHE_RAM_ATTR doEncoderA(void);
void ICACHE_RAM_ATTR doEncoderB(void);

volatile unsigned ICACHE_RAM_ATTR int encoder0Pos = 0;

void setup() {
  pinMode(encoder0PinA, INPUT_PULLUP);
  pinMode(encoder0PinB, INPUT_PULLUP);

  // encoder pin on interrupt 0 (pin 2)
  attachInterrupt(0, doEncoderA, CHANGE);

  // encoder pin on interrupt 1 (pin 3)
  attachInterrupt(1, doEncoderB, CHANGE);

  Serial.begin (115200);
}

void loop() 
{
  static volatile int a = 0x00u;
  a++;
  if(0x1FFFFu == a)
  {
    Serial.println (encoder0Pos, HEX);
    a = 0x00u;
  }
}

void ICACHE_RAM_ATTR doEncoderA(void) {
  // look for a low-to-high on channel A
  if (digitalRead(encoder0PinA) == HIGH) {

    // check channel B to see which way encoder is turning
    if (digitalRead(encoder0PinB) == LOW) {
      encoder0Pos = encoder0Pos + 1;         // CW
    }
    else {
      encoder0Pos = encoder0Pos - 1;         // CCW
    }
  }

  else   // must be a high-to-low edge on channel A
  {
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder0PinB) == HIGH) {
      encoder0Pos = encoder0Pos + 1;          // CW
    }
    else {
      encoder0Pos = encoder0Pos - 1;          // CCW
    }
  }
}

void ICACHE_RAM_ATTR doEncoderB(void) {
  // look for a low-to-high on channel B
  if (digitalRead(encoder0PinB) == HIGH) {

    // check channel A to see which way encoder is turning
    if (digitalRead(encoder0PinA) == HIGH) {
      encoder0Pos = encoder0Pos + 1;         // CW
    }
    else {
      encoder0Pos = encoder0Pos - 1;         // CCW
    }
  }

  // Look for a high-to-low on channel B

  else {
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder0PinA) == LOW) {
      encoder0Pos = encoder0Pos + 1;          // CW
    }
    else {
      encoder0Pos = encoder0Pos - 1;          // CCW
    }
  }
}

#if 0
void ICACHE_RAM_ATTR PinA(void);
void ICACHE_RAM_ATTR PinB(void);

static int pinA = 5; // Our first hardware interrupt pin is digital pin 2
static int pinB = 4; // Our second hardware interrupt pin is digital pin 3
volatile byte aFlag = 0; // let's us know when we're expecting a rising edge on pinA to signal that the encoder has arrived at a detent
volatile byte bFlag = 0; // let's us know when we're expecting a rising edge on pinB to signal that the encoder has arrived at a detent (opposite direction to when aFlag is set)
int encoderPos = 0; //this variable stores our current value of encoder position. Change to int or uin16_t instead of byte if you want to record a larger range than 0-255
int oldEncPos = 0; //stores the last encoder position value so we can compare to the current reading and see if it has changed (so we know when to print to the serial monitor)
int reading = 0; //somewhere to store the direct values we read from our interrupt pins before checking to see if we have moved a whole detent


void setup() 
{
  pinMode(pinA, INPUT_PULLUP); // set pinA as an input, pulled HIGH to the logic voltage (5V or 3.3V for most cases)
  pinMode(pinB, INPUT_PULLUP); // set pinB as an input, pulled HIGH to the logic voltage (5V or 3.3V for most cases)

  attachInterrupt(pinA,PinA,RISING); // set an interrupt on PinA, looking for a rising edge signal and executing the "PinA" Interrupt Service Routine (below)
  attachInterrupt(pinB,PinB,RISING); // set an interrupt on PinB, looking for a rising edge signal and executing the "PinB" Interrupt Service Routine (below)

  Serial.begin(115200); // start the serial monitor link
  Serial.println("Init done!");
}

void ICACHE_RAM_ATTR PinA(void)
{
  cli(); //stop interrupts happening before we read pin values

  reading = (digitalRead(pinB)<< 0x01u)& (digitalRead(pinA)); // read all eight pin values then strip away all but pinA and pinB's values

  if(reading == B00000011 && aFlag)  //check that we have both pins at detent (HIGH) and that we are expecting detent on this pin's rising edge
  {
    encoderPos = encoderPos - 2; //decrement the encoder's position count
    bFlag = 0; //reset flags for the next turn
    aFlag = 0; //reset flags for the next turn
  }
  else if (reading == B00000001) 
  {
    bFlag = 1; //signal that we're expecting pinB to signal the transition to detent from free rotation
  }
  else
  {
    /* do nothing */
  }
  
  sei(); //restart interrupts
}

void ICACHE_RAM_ATTR PinB(void)
{
  cli(); //stop interrupts happening before we read pin values

  reading = (digitalRead(pinB)<< 0x01u)& (digitalRead(pinA)); //read all eight pin values then strip away all but pinA and pinB's values

  if (reading == B00000011 && bFlag)  //check that we have both pins at detent (HIGH) and that we are expecting detent on this pin's rising edge
  {  
    encoderPos = encoderPos + 2; //increment the encoder's position count
    bFlag = 0; //reset flags for the next turn
    aFlag = 0; //reset flags for the next turn
  }
  else if (reading == B00000010)
  {
    aFlag = 1; //signal that we're expecting pinA to signal the transition to detent from free rotation
  }
  else
  {
    /* do nothing */
  }
  
  sei(); //restart interrupts
}

void loop()
{
  if(oldEncPos != encoderPos) 
  {
    Serial.println(encoderPos);
    
    oldEncPos = encoderPos;
  }
#if 0
  static volatile int a = 0x00u;
  a++;
  if(0xffff == a)
  {
    Serial.println("Main!");
    a = 0x00u;
  }
#endif
}
#endif