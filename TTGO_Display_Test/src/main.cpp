#include <Arduino.h>
#include <CAN.h>
#include "Cluster.h"
#include "Display.h"
#include "UDS.h"

TFT_eSPI tft = TFT_eSPI();
uint8_t rxData[8];


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

void flushRxData()
{
  uint8_t index = 0x00u;
  
  for(index = 0x00u; index < (uint8_t)(sizeof(rxData)/sizeof(rxData[0])); index++)
  {
    rxData[index] = 0x00u;
  }

}

void CAN_Main() 
{
  uint16_t receivedCANID = 0x0000u;
  uint8_t index = 0x00u;

  // try to parse packet
  int packetSize = CAN.parsePacket();

  if(tft.getCursorY() > 270)
  {
    tft.setCursor(0,0,2);
    tft.fillScreen(TFT_GREY);
  }

  if (packetSize) 
  {
    receivedCANID = CAN.packetId();
    DisplayPrint(tft, "ID: 0x");
    DisplayPrint(tft, receivedCANID, HEX);        

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
        rxData[index] = (uint8_t)CAN.read();
        DisplayPrint(tft, (int)rxData[index], HEX);   
        DisplayPrint(tft, " ");    
        index++; 
      }
      index = 0x00u;

      if(UDS_REQUEST_ID == receivedCANID)
      {
        int8_t result = UDS_setRxBuffer(rxData);
        UDS_process();
        flushRxData();
      }
      else
      {
        flushRxData();
      }

      DisplayWrite(tft, " ");
    }
  }
}