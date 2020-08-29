#ifndef LCD_H_
#define LCD_H_

#include <Arduino.h>
#include <LiquidCrystal_PCF8574.h>

uint8_t isLCDInited(void);
void lcdInit(void);
void lcdAccessAllowed(void);
void lcdAccessDenied(void);
void lcdAvailableParkingSpotsNr(void);
void lcdSmokeDetected(void);
void lcdPrint(uint32_t data);

#endif