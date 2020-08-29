#ifndef ACCESSENTER_H_
#define ACCESSENTER_H_

#include <Arduino.h>

#define ACCESS_DENIED   0x00u
#define ACCESS_ALLOWED  0x01u
#define CARTELA_ALBA    0x492AB998u

void accessEnter_main(void);
void accessEnterInit(void);

#endif