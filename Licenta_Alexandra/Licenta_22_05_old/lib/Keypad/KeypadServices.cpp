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

/**************************************************/
/***************Local functions********************/
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
uint8_t keypadIsPasswordAvailable(void)
{
    uint8_t status = 0x00;
    static uint8_t count = 0x00u;
    static uint8_t password[] = {0, 0, 0, 0,};

    if(count < NUMBER_OF_PASS_DIGITS)
    {
        password[count] = customKeypad.getKey();
        //lcdPrint((uint32_t)password[count]);
        count ++;
    }
    else if(count == NUMBER_OF_PASS_DIGITS)
    {
        keypadPassword = (uint32_t)((uint32_t)((uint32_t)password[0] << 24)) |
                                   ((uint32_t)((uint32_t)password[1] << 16)) |
                                   ((uint32_t)((uint32_t)password[2] << 8))  |
                                               (uint32_t)password[3];
        count = 0x00u;
        password[0] = 0x00u;
        password[1] = 0x00u;
        password[2] = 0x00u;
        password[3] = 0x00u;
        status = 0x01u;
    }
    else
    {
        count = 0x00u;
        password[0] = 0x00u;
        password[1] = 0x00u;
        password[2] = 0x00u;
        password[3] = 0x00u;
        keypadPassword = 0x00u;
    }

    return status;
}