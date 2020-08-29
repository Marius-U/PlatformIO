#ifndef GIGITALIO_H_
#define GIGITALIO_H_

/******************Includes************************/
#include <Arduino.h>

/**************************************************/

/******************Defines************************/
#define LOC3                4
#define LOC2                A1
#define LOC1                A0
#define VENT                3
#define GAZ                 A3
#define SEMAPHORE_RED       0
#define SEMAPHORE_GREEN     1

#define OFF                         0x00u
#define ON                          0x01u
#define GAZSENSOR_TRIGGERED         LOW
#define GAZSENSOR_NOT_TRIGGERED     HIGH
#define SPOT_OCCUPIED               LOW
#define SPOT_FREE                   HIGH
#define RED                         0x00u
#define GREEN                       0x01u

/**************************************************/

/***************External functions*****************/

void digitalInit(void);
uint8_t digitalGetGazStatus(void);
void digitalSetAirVent(uint8_t value);
uint8_t digilatGetParkingSpotsStatus(void);
/**************************************************/

#endif