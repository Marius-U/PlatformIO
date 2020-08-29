#include <LCD.h>
#include <DigitalIO.h>
/***************Local variables********************/
/**************************************************/
LiquidCrystal_PCF8574 lcd(0x27);
static uint8_t lcdIsInited;

/***************Local functions********************/
/**************************************************/

/***************External variables*****************/
/**************************************************/

/***************External functions*****************/
/**************************************************/



uint8_t isLCDInited(void)
{
    return lcdIsInited;
}

void lcdInit(void)
{
    if(!lcdIsInited)
    {
        lcd.begin(16, 2);
        lcd.setBacklight(255);
        lcd.setCursor(0, 0);
        lcdIsInited = 0x01u;
        lcdAvailableParkingSpotsNr();
    }
}

void lcdPrint(const char *str)
{
    lcdClear();
    lcd.write(str);
}

void lcdPrintChar(char ch, uint8_t cursPos)
{
    lcd.setCursor(cursPos,0);
    lcd.write(ch);
}

void lcdClear(void)
{
    lcd.clear();
}

void lcdAccessAllowed(void)
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.write("Accesul este");
    lcd.setCursor(0, 1);
    lcd.write("permis!");
}

void lcdAccessDenied(void)
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.write("Accesul este");
    lcd.setCursor(0, 1);
    lcd.write("respins!");
}

void lcdAvailableParkingSpotsNr(void)
{
    uint8_t availableParkingSpotsNumber = 0x00u;
    char numberToChar = 0x51;
    availableParkingSpotsNumber = digilatGetParkingSpotsStatus();
    
    /*read available parking spots number from EEPROM*/
    numberToChar = availableParkingSpotsNumber + 0x30u;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.write("Locuri");
    lcd.setCursor(0, 1);
    lcd.write("disponibile:");
    lcd.print(numberToChar);

}

void lcdSmokeDetected(void)
{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.write("Atentie! Prea");
    lcd.setCursor(0,1);
    lcd.write("mult CO in aer!");
}