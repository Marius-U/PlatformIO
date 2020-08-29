#ifndef ACCESSENTER_H_
#define ACCESSENTER_H_

#include <Arduino.h>

#define ACCESS_DENIED           0x5Au
#define ACCESS_ALLOWED          0xA5u
#define GATE_CLOSED             0x00u
#define GATE_OPPENED            0x01u
#define GATE_OPENED_TIMEOUT     0x12Cu      /*~= 4500ms*/
#define CARTELA_ALBA            0x492AB998u

void accessEnter_main(void);
void accessEnterInit(void);

#endif