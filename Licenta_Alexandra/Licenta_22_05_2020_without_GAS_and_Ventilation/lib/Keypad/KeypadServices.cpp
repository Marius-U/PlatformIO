#include <KeypadServices.h>
#include <LCD.h>

/***************Local variables********************/
static uint32_t keypadPassword;
static uint8_t keypasIsKeypadInited;
const byte ROWS = 4; 
const byte COLS = 3;
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[ROWS] = {13, 12, 11, 10}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {9, 8, 7}; //connect to the column pinouts of the keypad
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
static uint8_t keypadShiftPosition[4] = {0u, 8u, 16u, 24u};
/**************************************************/
/***************Local functions********************/

char keypadGetKey(void);

/**************************************************/

/***************External variables*****************/
/**************************************************/

/***************External functions*****************/
/**************************************************/
 

uint8_t isKeypadInited(void)
{
    return keypasIsKeypadInited;
}

void keypadInit(void)
{
    if(!keypasIsKeypadInited)
    {
        
       keypasIsKeypadInited = 0x01;
    }
}

uint32_t keypadGetPassword(void)
{
    return keypadPassword;
}

void keypadPasswordConsumed(void)
{
    keypadPassword = 0x00000000u;
}

uint8_t keypadIsPasswordAvailable(void)
{
    uint8_t status = 0x00;
    static uint8_t cursorPos = 0x06u;
    char key = 0x00u;
    static uint8_t countKeys = 0x00u;

    key = keypadGetKey();
    if(key)
    {
        lcdPrint("PIN: ");
        lcdPrintChar(key,cursorPos);
        keypadPassword |= (uint32_t)(key - 0x30) << keypadShiftPosition[countKeys];
        countKeys ++;
        cursorPos++;
    }
    if(NUMBER_OF_PASS_DIGITS == countKeys)
    {
        countKeys = 0x00u;
        cursorPos = 0x06u;
        status = 0x01u;
    }

    return status;
}

char keypadGetKey(void)
{
    char key = 0x00u;
    key = customKeypad.getKey();
    return key;
}
