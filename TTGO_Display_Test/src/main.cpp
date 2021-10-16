#include <Arduino.h>
#include <CAN.h>
#include "Cluster.h"
#include "Display.h"

TFT_eSPI tft = TFT_eSPI();


void CAN_Main();

void setup(void) {
  Serial.begin(57600); // For debug
  //Cluster_Init(tft);
  Display_Init(tft);

  CAN.setPins(27,26);
  // start the CAN bus at 500 kbps
  if (!CAN.begin(500E3)) 
  {
    Serial.println("Starting CAN failed!");
    while (1);
  }
}


void loop() 
{
  static char flag = 0x00u;

  if(Serial.available())
  {
    flag = Serial.read();
  }

  if(flag == 'c')
  {
    Display_Init(tft);
    DisplayWrite(tft, "Ceva fain!");
    flag = 0x01u;
  }
  else if(flag == 'i')
  {
    DisplayWrite(tft, "O iubesc pe Lavi!");
    flag = 0x01u;
  }
  else if (flag == 0x00u)
  {
    //Cluster_Main();
    CAN_Main();

  }
  else
  {

  }
  
}

void CAN_Main() 
{
  // try to parse packet
  int packetSize = CAN.parsePacket();

  if(tft.getCursorY() > 270)
  {
    tft.setCursor(0,0,2);
    tft.fillScreen(TFT_GREY);
  }

  if (packetSize) {
    // received a packet
    //DisplayWrite(tft, "Received ");

    if (CAN.packetExtended()) {
      //DisplayWrite(tft, "extended ");
    }

    if (CAN.packetRtr()) {
      // Remote transmission request, packet contains no data
      DisplayWrite(tft, "RTR ");
    }

    DisplayPrint(tft, "ID: 0x");
    DisplayPrint(tft, CAN.packetId(), HEX);        

    if (CAN.packetRtr()) 
    {
      DisplayPrint(tft, " DLC: ");
      DisplayPrint(tft, CAN.packetDlc());  
      DisplayPrint(tft, " ");      
    } 
    else 
    {
      DisplayPrint(tft, " DLC: ");
      DisplayPrint(tft, packetSize);
      DisplayPrint(tft, " ");          

      // only print packet data for non-RTR packets
      while (CAN.available()) {
        DisplayPrint(tft, CAN.read(), HEX);   
        DisplayPrint(tft, " ");     
      }
      DisplayWrite(tft, " ");
    }

    //Serial.println();
  }
}