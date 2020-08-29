#include <AccessEnter.h>
#include <RFID.h>
#include <LCD.h>
#include <ServoService.h>
/***************Local variables********************/
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
    lcdPrint(1);
}

void accessEnter_main(void)
{
    uint32_t rfidData = 0x00000000u;
    uint8_t status = 0x00u; //by default access is denied 

    rfidData = rfidReadData();
    
    status = accessEnterValidateAccess(rfidData);

    if (status == ACCESS_ALLOWED)
    {
        /* set semaphore to green */
        lcdAccessAllowed();
        servoAccessGateOpen();
        /*set a timer to close the gate*/
    }
    else
    {
        /* set semaphore to red  */
        //lcdPrint(rfidData);
        lcdAccessDenied();
        servoAccessGateClose();
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