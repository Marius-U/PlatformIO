#include <SafetyMonitor.h>
#include <DigitalIO.h>
#include <LCD.h>
#include <ServoService.h>
/***************Local variables********************/
static uint8_t gazSensorStatus;
static uint8_t gazSensorPrevStatus;
/**************************************************/

/***************Local functions********************/
/**************************************************/

/***************External variables*****************/
/**************************************************/

/***************External functions*****************/
/**************************************************/
void safetyMonitorInit(void)
{

}
void safetyMonitor_main(void)
{
    
    gazSensorStatus = digitalGetGazStatus();      

    if(GAZSENSOR_TRIGGERED == gazSensorStatus)    //process the gaz sensor reading
    {
        digitalSetAirVent(ON);
        if(gazSensorStatus != gazSensorPrevStatus)
        {
            lcdSmokeDetected();
            servoAllGatesOpen();
            gazSensorPrevStatus = gazSensorStatus;
        }
    }
    else if (GAZSENSOR_NOT_TRIGGERED == gazSensorStatus)
    {
        digitalSetAirVent(OFF);
        if(gazSensorStatus != gazSensorPrevStatus)
        {
            lcdAvailableParkingSpotsNr();
            servoAllGatesClosed();
            gazSensorPrevStatus = gazSensorStatus;
        }
    }
    else
    {
        /* code */
    }
    
}