#ifndef KEYPADSERVICES_H_
#define KEYPADSERVICES_H_

#include <Arduino.h>
#include <Keypad.h>

#define NUMBER_OF_PASS_DIGITS   0x04u

uint8_t isKeypadInited(void);
void keypadInit(void);
uint32_t keypadGetPassword(void);
uint8_t keypadIsPasswordAvailable(void);

#endif