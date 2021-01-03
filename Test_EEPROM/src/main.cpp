/* 
 ESP8266 DIAGNOSTICS (DIAG) - ESP8266DIAG.ino

 Modified/extended by codebeat 01/25/2018

 ESP8266 CheckFlashConfig by Markus Sattler

 This sketch tests if the EEPROM settings of the IDE match to the Hardware
*/
#include <Arduino.h>
#include "spi_flash.h"

#include <FS.h>
#include <ESP8266WiFi.h>
//#include <ESP8266WebServer.h>
#include <Wire.h>               // Serial communication 
#include "spi_flash.h"
#include <EEPROM.h>             // Reading or writing to build-in EEPROM

extern "C" {
  #include "user_interface.h"
}

 // NodeMCU Pin names to GPIO, NodeMCU has weird pin mapping.
 // https://github.com/esp8266/Arduino/blob/master/variants/nodemcu/pins_arduino.h#L37-L59
 // Pin numbers written on the board itself do not correspond to ESP8266 GPIO pin numbers. 
 // Here defines to make using this board easier (If you want to use NodeMCU pin 5, 
 // use D5 for pin number, and it will be translated to 'real' GPIO pin 14):
#define D0 16 // supports PWM
#define D1  5 // I2C Bus SCL (clock)
#define D2  4 // I2C Bus SDA (data)
#define D3  0
#define D4  2 // Same as "LED_BUILTIN", but inverted logic
#define D5 14 // SPI Bus SCK (clock)
#define D6 12 // SPI Bus MISO 
#define D7 13 // SPI Bus MOSI
#define D8 15 // SPI Bus SS (CS)
#define D9  3 // RX0 (Serial console)
#define D10 1 // TX0 (Serial console)

#define SD0   7
#define SD1   8
#define SD2   9
#define SD3   10
#define SDCMD 11

// Connection properties
#define SYS_SSID      "Mures_98"
#define SYS_SSID_PWD  "66267676"


//WiFiServer server(80);
FSInfo fs_info;

char* getHertzShortNotation( double hertz )        
{
                 double thz = 1000000000000;
                 double ghz = 1000000000;
                 double mhz = 1000000;
                 double khz = 1000;


                 static char returnSize[28];

                 memset( &returnSize[0], 0, sizeof( returnSize ));
                 if( hertz >= thz )
                     sprintf(returnSize, "%.2f Thz", (double)hertz/thz); // Maybe for future ;-)        
                 else if( hertz >= ghz && hertz < thz )
                     sprintf(returnSize, "%.2f Ghz", (double)hertz/ghz);
                 else if( hertz >= mhz && hertz < ghz )
                     sprintf(returnSize, "%.2f Mhz", (double)hertz/mhz);   
                 else if( hertz >= khz && hertz < mhz )
                     sprintf(returnSize, "%.2f Khz", (double)hertz/khz);
                 else if ( hertz < khz)
                     sprintf(returnSize, "%.2f Hz", hertz);
                 else
                     sprintf(returnSize, "%.2f Hz", hertz);


                 return returnSize;
}


char* getBytesShortNotation( double Bytes )        
{
                 double tb = 1099511627776;
                 double gb = 1073741824;
                 double mb = 1048576;
                 double kb = 1024;


                 static char returnSize[28];


                 memset( &returnSize[0], 0, sizeof( returnSize ));
                 if( Bytes >= tb )
                     sprintf(returnSize, "%.2f TB", (double)Bytes/tb);        
                 else if( Bytes >= gb && Bytes < tb )
                     sprintf(returnSize, "%.2f GB", (double)Bytes/gb);
                 else if( Bytes >= mb && Bytes < gb )
                     sprintf(returnSize, "%.2f MB", (double)Bytes/mb);   
                 else if( Bytes >= kb && Bytes < mb )
                     sprintf(returnSize, "%.2f KB", (double)Bytes/kb);
                 else if ( Bytes < kb)
                     sprintf(returnSize, "%.2f B", Bytes);
                 else
                     sprintf(returnSize, "%.2f B", Bytes);


                 return returnSize;
}



void setup(void) 
{
    Serial.begin(9600);
    EEPROM.begin( SPI_FLASH_SEC_SIZE );
    SPIFFS.begin();
    SPIFFS.info(fs_info);
    WiFi.begin( SYS_SSID, SYS_SSID_PWD );
    //server.begin();
}

void loop() {

    uint32_t    realSize = ESP.getFlashChipRealSize();
    uint32_t    ideSize = ESP.getFlashChipSize();
    FlashMode_t ideMode = ESP.getFlashChipMode();

    Serial.println("\n\nESP DIAG BY CODEBEAT\n" );
    Serial.println( "------ CHIP/MCU/VSOFT" );
    Serial.printf("ESP  chip ID        : %08X\n"   , ESP.getChipId() );
    Serial.printf("MCU  Frequency      : %u (%s)\n", ESP.getCpuFreqMHz(), 
                                                     (char *)getHertzShortNotation( ESP.getCpuFreqMHz()*1000*1000 ));
    Serial.printf("Core version        : %s\n"     , ESP.getCoreVersion().c_str() );
    Serial.printf("SDK  version        : %s\n"     , ESP.getSdkVersion() );

    Serial.println("\n");

    Serial.println( "----------------- RAM" );
    Serial.printf("Free                : %u Bytes (%s)\n", 
                                             system_get_free_heap_size(), 
                                             (char *)getBytesShortNotation( system_get_free_heap_size() ) );
    Serial.println("\n");



    Serial.println( "--------------- FLASH" );
    Serial.printf("Flash real id       : %08X\n", ESP.getFlashChipId());

    Serial.printf("Flash real size     : %u Bytes (%s) ", realSize, (char *)getBytesShortNotation( realSize ) );
    if( ideSize != realSize ) 
      { Serial.println(" <-- DOESN'T MATCH!"); } 
    else { Serial.println("OK!"); }

    Serial.printf("Flash ide  size     : %u Bytes (%s) ", ideSize, (char *)getBytesShortNotation( ideSize ) );
    if( ideSize != realSize ) 
      { Serial.println(" <-- DOESN'T MATCH!"); } 
    else { Serial.println("OK!"); }

    Serial.printf("Flash ide speed     : %u Hz    (%s)\n", ESP.getFlashChipSpeed(), (char *)getHertzShortNotation( ESP.getFlashChipSpeed() ));
    Serial.printf("Flash ide  mode     : %s\n", 
                      ( ideMode == FM_QIO ? "QIO" : 
                        ideMode == FM_QOUT ? "QOUT" : 
                        ideMode == FM_DIO ? "DIO" : 
                        ideMode == FM_DOUT ? "DOUT" : 
                        "UNKNOWN"
                      )
                 );

    Serial.println("\n");

    Serial.println( "-------- FLASH EEPROM" );
    Serial.printf("Max emulated size   : %u Bytes (%s)\n", EEPROM.length(), (char *)getBytesShortNotation( EEPROM.length() ) );

    Serial.println("\n");


    Serial.println( "------ SPIFFS FILESYS" );
    Serial.printf("Used                : %u Bytes (%s)\n", fs_info.usedBytes , (char *)getBytesShortNotation( fs_info.usedBytes ) );
    Serial.printf("Total size          : %u Bytes (%s)\n", fs_info.totalBytes, (char *)getBytesShortNotation( fs_info.totalBytes ) );
    Serial.printf("Block size          : %u Bytes (%s)\n", fs_info.blockSize , (char *)getBytesShortNotation( fs_info.blockSize ) );
    Serial.printf("Logical Pages       : %u\n"           , fs_info.pageSize );
    //Serial.printf("Pages x Block       : %u Bytes (%s)\n", fs_info.pageSize * fs_info.blockSize, (char *)getBytesShortNotation( fs_info.pageSize * fs_info.blockSize ) );
    Serial.printf("Max open files      : %u files\n"     , fs_info.maxOpenFiles  );
    Serial.printf("Max path length     : %u chars\n"     , fs_info.maxPathLength );

    Serial.println("\n");

    Serial.println( "-------- SPIFFS FILES" );
    Dir oDir = SPIFFS.openDir("/");
    uint16_t iFound = 0;
    while( oDir.next() ) 
    {
      ++iFound;
      File f = oDir.openFile("r");
      Serial.printf("SPIFFS /> %u. %s : %u Bytes (%s)\n", 
                     iFound,
                     oDir.fileName().c_str(),
                     f.size(),
                     (char *)getBytesShortNotation( f.size() )
                   );
    }
    if( iFound == 0 )
     { Serial.println( "SPIFFS /> No file(s) found." ); }

    Serial.println("\n");

    Serial.println( "-------- PROGRAM MEM" );
    Serial.printf("Sketch  size        : %u Bytes (%s)\n", ESP.getSketchSize(), 
                                                          (char *)getBytesShortNotation( ESP.getSketchSize() ));
    Serial.printf("Sketch  free size   : %u Bytes (%s)\n", ESP.getFreeSketchSpace(), 
                                                          (char *)getBytesShortNotation( ESP.getFreeSketchSpace() ));
    Serial.printf("Program total space : %u Bytes (%s)\n", ESP.getSketchSize()+ESP.getFreeSketchSpace(), 
                                                          (char *)getBytesShortNotation( ESP.getSketchSize()+ESP.getFreeSketchSpace() ) );
    Serial.printf("Sketch MD5          : (%s)\n", ESP.getSketchMD5().c_str() );

    Serial.println("\n");

    Serial.println( "------- WIFI NETWORK" );
    byte mac[6];
    WiFi.macAddress(mac);
    Serial.printf("MAC address         : %02X:%02X:%02X:%02X:%02X:%02X\n", 
                                                           mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    Serial.printf("Connected           : %s\n", WiFi.status() == WL_CONNECTED?"Yes":"No" );
    Serial.printf("SSID                : %s\n", WiFi.SSID().c_str() );
    IPAddress ipaddr = WiFi.localIP();
    Serial.printf("IP Address          : %u.%u.%u.%u\n", ipaddr[0], ipaddr[1], ipaddr[2], ipaddr[3] );
    Serial.printf("Signal (RSSI)       : %i dBm\n", WiFi.RSSI() );

    Serial.println("\n\n");
    Serial.println( "------------------ WAIT 20 SEC TO REFRESH");
   delay(20000);
}