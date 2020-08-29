#ifndef RFID_H_
#define RFID_H_

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PN532.h>

#define PN532_IRQ   (2)
#define PN532_RESET (13)

uint8_t isRfidInited(void);
void rfidInit(void);
uint32_t rfidReadData(void);


#endif