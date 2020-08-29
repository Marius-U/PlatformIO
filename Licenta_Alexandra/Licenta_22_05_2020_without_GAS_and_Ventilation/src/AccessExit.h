#ifndef ACCESSEXIT_H_
#define ACCESSEXIT_H_

#include <Arduino.h>

#define GATE_CLOSED             0x00u
#define GATE_OPPENED            0x01u
#define GATE_OPENED_TIMEOUT     0x12Cu      /*~= 4500ms*/

void acessExitInit(void);
void accessExit_main(void);

#endif