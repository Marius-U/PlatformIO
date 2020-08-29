#ifndef DEBUGG_H_
#define DEBUGG_H_

#include <Arduino.h>

#define STD_OFF     0x00u
#define STD_ON      0x01u
#define DEBUGG      STD_OFF

#if (DEBUGG == STD_ON)
void debuggInit(void);
void debuggPrint(String msg);
#endif

#endif