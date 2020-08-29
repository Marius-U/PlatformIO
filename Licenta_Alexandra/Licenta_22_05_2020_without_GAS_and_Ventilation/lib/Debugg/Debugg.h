#ifndef DEBUGG_H_
#define DEBUGG_H_

#include <Arduino.h>

#define DEBUGG STD_OFF

#if (DEBUGG == STD_ON)
void debuggInit(void);
void debuggPrint(String msg);
#endif

#endif