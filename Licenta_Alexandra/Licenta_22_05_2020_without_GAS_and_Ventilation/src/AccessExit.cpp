#include <AccessExit.h>
#include <LCD.h>
#include <ServoService.h>
#include <KeypadServices.h>

/***************Local variables********************/
/**************************************************/
static uint8_t accessExitGateStatus;
static uint16_t accessExitGateOpenTimeout;
/***************Local functions********************/
/**************************************************/

/***************External variables*****************/
/**************************************************/

/***************External functions*****************/
/**************************************************/

void acessExitInit(void)
{
    lcdInit();
    servoGatesInit();
}
void accessExit_main(void)
{
    uint64_t status = 0x00u;
    uint32_t password = 0x00000000u;

    if(GATE_CLOSED == accessExitGateStatus)
    {
        status = keypadIsPasswordAvailable();     

        if(status)
        {
            password = keypadGetPassword();
            if(0x04030201u == password)
            {
                servoExitGateOpen();
                accessExitGateStatus = GATE_OPPENED;
                lcdClear();
                lcdPrint("O zi buna!");
            }
            else if(0xFFFFFFFFu == password)
            {
                //implement custom action like "Learn new code."                
            }
            else if(0x01010101u == password)
            {
                lcdClear();
                lcdPrint("Bingo!");              
            }
            else
            {
                lcdClear();
                lcdPrint("PIN gresit!"); 
                accessExitGateStatus = GATE_OPPENED; /*Simulate open gate to enable timeout mechanism.*/
            }
            keypadPasswordConsumed();
        }
    }
    else
    {
        accessExitGateOpenTimeout++;                           /*Gate is open, increment timeout to close the gate*/
        if (GATE_OPENED_TIMEOUT == accessExitGateOpenTimeout)  /*4500ms passed, close the gate*/
        {
            servoExitGateClose();
            lcdAvailableParkingSpotsNr();
            accessExitGateOpenTimeout = 0x0000u;               /*reset timer*/
            accessExitGateStatus = GATE_CLOSED;                /*switch gate status*/
        }
    }
    
}