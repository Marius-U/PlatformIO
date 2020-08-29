#include <DigitalIO.h>
#include <Debugg.h>

/***************Local variables********************/
/**************************************************/

/***************Local functions********************/
/**************************************************/

/***************External variables*****************/
/**************************************************/


void digitalInit(void)
{
    pinMode(LOC1,INPUT);
    pinMode(LOC2,INPUT);
    pinMode(LOC3,INPUT);
    pinMode(GAZ, INPUT);
    pinMode(VENT, OUTPUT);
    digitalWrite(VENT, LOW); //after pin initialization for ventilator make sure it is turned off.
#if(DEBUGG == STD_OFF)
    pinMode(SEMAPHORE_RED, OUTPUT);
    digitalWrite(SEMAPHORE_RED, HIGH);
    pinMode(SEMAPHORE_GREEN, OUTPUT);
    digitalWrite(SEMAPHORE_GREEN, LOW);
#endif
}

/*digilatGetParkingSpotsStatus:
 *      Read proximity sensors for all parking spots to determin how many are occupied and store result in EEPROM.
 */
void digilatGetParkingSpotsStatus(void)
{
    uint8_t loc1 = digitalRead(LOC1);
    uint8_t loc2 = digitalRead(LOC2);
    uint8_t loc3 = digitalRead(LOC3);

    /*if read value is different from global ram read at start-up 
        writte it to EEPROM (status1, status2, status3, total)
      else
        do nothing
    */
}

/*digitalGetGazStatus:
 *      Read gaz sensors to determin if air vent needs to be turned on and store result in EEPROM.
 */
uint8_t digitalGetGazStatus(void)
{
    uint8_t gaz = digitalRead(GAZ);

    /*if read value is different from global ram read at start-up 
        writte it to EEPROM (status gaz)
      else
        do nothing
    */
   return gaz;
}

void digitalSetAirVent(uint8_t value)
{
    if(ON == value)
    {
        digitalWrite(VENT, HIGH);
    }
    else
    {
        digitalWrite(VENT, LOW);
    }
    
}

void  digitalSemaphoreSetStatus(uint8_t status)
{
    if(status == GREEN)
    {
#if(DEBUGG == STD_OFF)
        digitalWrite(SEMAPHORE_RED, LOW);
        digitalWrite(SEMAPHORE_GREEN, HIGH);
#endif  
    }
    else //RED
    {
        digitalWrite(SEMAPHORE_RED, HIGH);
        digitalWrite(SEMAPHORE_GREEN, LOW);
    }
}