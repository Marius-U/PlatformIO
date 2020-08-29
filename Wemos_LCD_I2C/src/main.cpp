#include <Arduino.h>

#include <LiquidTWI.h>
#include <Wire.h>

LiquidTWI lcd(0);



int incomingByte = 0; // for incoming serial data

void setup() {
  lcd.begin(16,2);
  lcd.setBacklight(true);
  lcd.print("LCD inited!");
  Serial.begin(9600);
}



void loop() {
 static uint8_t line = 0;
 static uint8_t col = 0;
 static uint8_t a = 0;

  // send data only when you receive data:
  if (Serial.available() > 0) 
  {
    // read the incoming byte:
    incomingByte = Serial.read();
    a = (uint8_t) incomingByte;

    lcd.setCursor(col,line);
    lcd.write(a);
    col ++;
    if(col == 16)
    {
      col = 0;
      if(line == 0)
      {
        line = 1;
      }
      else
      {
        line = 0;
      }
    }
  }
}
