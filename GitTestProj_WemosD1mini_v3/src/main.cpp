#include <Arduino.h>

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

  attachInterrupt(0,PinA,RISING); // set an interrupt on PinA, looking for a rising edge signal and executing the "PinA" Interrupt Service Routine (below)
  attachInterrupt(1,PinB,RISING); // set an interrupt on PinB, looking for a rising edge signal and executing the "PinB" Interrupt Service Routine (below)

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
}