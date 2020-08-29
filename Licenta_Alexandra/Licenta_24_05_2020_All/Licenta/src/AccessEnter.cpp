#include <AccessEnter.h>
#include <RFID.h>
#include <LCD.h>
#include <ServoService.h>
#include <DigitalIO.h>
/***************Local variables********************/
static uint8_t accessEnterGateStatus;
static uint16_t accessEnterGateOpenTimeout;
/**************************************************/
/***************Local functions********************/
/**************************************************/
 uint8_t accessEnterValidateAccess(uint32_t rfidData);
/***************External variables*****************/
/**************************************************/

/***************External functions*****************/
/**************************************************/
void accessEnterInit(void)
{
    lcdInit();
    rfidInit();
    servoGatesInit();
    digitalInit();
}

void accessEnter_main(void)
{
    uint32_t rfidData = 0x00000000u;
    uint8_t status = 0x00u; //by default access is denied 

    if(GATE_CLOSED == accessEnterGateStatus)
    {
        rfidData = rfidReadData();
    
        status = accessEnterValidateAccess(rfidData);

        if (status == ACCESS_ALLOWED)
        {
            digitalSemaphoreSetStatus(GREEN);
            lcdAccessAllowed();
            servoAccessGateOpen();
            /*set a timer to close the gate*/
            accessEnterGateStatus = GATE_OPPENED;
        }
        else if (status == ACCESS_DENIED)
        {
            digitalSemaphoreSetStatus(RED);         /* set semaphore to red  */
            lcdAccessDenied();
            servoAccessGateClose();
            accessEnterGateStatus = GATE_OPPENED;  /*Simulate open gate to enable timeout mechanism.*/
        }
        else
        {
            /*do nothing, missread*/
        }
    }
    else
    {
        accessEnterGateOpenTimeout++;                           /*Gate is open, increment timeout to close the gate*/
        if (GATE_OPENED_TIMEOUT == accessEnterGateOpenTimeout)  /*4500ms passed, close the gate*/
        {
            digitalSemaphoreSetStatus(RED);                     /* set semaphore to red  */
            servoAccessGateClose();
            lcdAvailableParkingSpotsNr();
            accessEnterGateOpenTimeout = 0x0000u;               /*reset timer*/
            accessEnterGateStatus = GATE_CLOSED;                /*switch gate status*/
        }
    }
    
}

 uint8_t accessEnterValidateAccess(uint32_t rfidData)
 {
    uint8_t status = ACCESS_DENIED;     //by default access is denied
    uint32_t accessCode = 0x00000000u;

    /* for all access codes in EEPROM 
        read code
            if code == rfidData
                status = 0x01u;
    */

   accessCode = CARTELA_ALBA;
   if(rfidData == accessCode)
   {
        status = ACCESS_ALLOWED;       
   }
   return status;
 }