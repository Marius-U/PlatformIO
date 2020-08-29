#ifndef DEBUGG_H_
#define DEBUGG_H_

#include <Arduino.h>

#define DEBUGG STD_ON

#if (DEBUGG == STD_ON)
void debuggInit(void);
void debuggPrint(String msg);
#endif

#endif