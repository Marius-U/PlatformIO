#include <SafetyMonitor.h>
#include <DigitalIO.h>
/***************Local variables********************/
/**************************************************/

/***************Local functions********************/
/**************************************************/

/***************External variables*****************/
/**************************************************/

/***************External functions*****************/
/**************************************************/

void safetyMonitor_main(void)
{
    uint8_t gazSensor = 0x00u;
    
    gazSensor = digitalGetGazStatus();      

    if(GAZSENSOR_TRIGGERED == gazSensor)    //process the gaz sensor reading
    {
        digitalSetAirVent(ON);
    }
    else if (GAZSENSOR_NOT_TRIGGERED == gazSensor)
    {
        digitalSetAirVent(OFF);
    }
    else
    {
        /* code */
    }
    
}