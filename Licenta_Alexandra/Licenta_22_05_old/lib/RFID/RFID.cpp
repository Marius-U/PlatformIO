#include <RFID.h>
#include <Debugg.h>
/***************Local variables********************/
/**************************************************/
static uint8_t rfidIsInited;
/***************Local functions********************/
/**************************************************/

/***************External variables*****************/
/**************************************************/

Adafruit_PN532 nfc(PN532_IRQ, PN532_RESET);

/***************External functions*****************/
/**************************************************/
uint8_t isRfidInited(void)
{
    return rfidIsInited;
}
void rfidInit(void)
{
   // if(!rfidIsInited)
   // {
        nfc.begin();

#if(DEBUGG == OFF)

        nfc.SAMConfig();

#else
        uint32_t versiondata = nfc.getFirmwareVersion();
        if (! versiondata) {
            Serial.print("Didn't find PN53x board");
            while (1); // halt
        }

        // Got ok data, print it out!
        Serial.print("Found chip PN5"); Serial.println((versiondata>>24) & 0xFF, HEX); 
        Serial.print("Firmware ver. "); Serial.print((versiondata>>16) & 0xFF, DEC); 
        Serial.print('.'); Serial.println((versiondata>>8) & 0xFF, DEC);

        // configure board to read RFID tags
        nfc.SAMConfig();

        Serial.println("Waiting for an ISO14443A Card ...");
#endif
        rfidIsInited = 0x01u;
   // }
}

uint32_t rfidReadData(void)
{
    uint8_t success;
    uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
    uint8_t uidLength;
    uint32_t cardid = 0x00000000u;

    // Wait for an ISO14443A type cards (Mifare, etc.).  When one is found
    // 'uid' will be populated with the UID, and uidLength will indicate
    // if the uid is 4 bytes (Mifare Classic) or 7 bytes (Mifare Ultralight)
    success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);

    if (success) 
    {
        // Display some basic information about the card
#if(DEBUGG == STD_ON)
        // Serial.println("Found an ISO14443A card");
        // Serial.print("  UID Length: ");
        // Serial.print(uidLength, DEC);
        // Serial.println(" bytes");
        // Serial.print("  UID Value: ");
        // nfc.PrintHex(uid, uidLength);
#endif
        if (uidLength == 4)
        {
            // We probably have a Mifare Classic card ... 
            cardid = uid[0];
            cardid <<= 8;
            cardid |= uid[1];
            cardid <<= 8;
            cardid |= uid[2];  
            cardid <<= 8;
            cardid |= uid[3]; 
#if(DEBUGG == STD_ON)
            Serial.print("Seems to be a Mifare Classic card #");
            Serial.println(cardid);
            Serial.println("");
#endif
        }
    }
    return cardid;
}