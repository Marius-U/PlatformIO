#include <AccessExit.h>
#include <LCD.h>
#include <ServoService.h>
#include <KeypadServices.h>

/***************Local variables********************/
/**************************************************/

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

    status = keypadIsPasswordAvailable();
    if(status)
    {
        password = keypadGetPassword();
        if(0x1234 == password)
        {
            servoExitGateOpen();
            lcdAvailableParkingSpotsNr();
        }
        else
        {
            // servoExitGateClose();
            // lcdAvailableParkingSpotsNr();
            //lcdPrint(password);
        }
    }
}