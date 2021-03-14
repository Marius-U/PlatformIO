#include <Arduino.h>
#include <EEPROM.h>


#if 1
void setup() {
  Serial.begin(9600);
  EEPROM.begin(512);

  EEPROM.write(0x05,0xFF);
  EEPROM.write(0x06,0xFF);
  EEPROM.write(0x07,0xFF);
  EEPROM.write(0x08,0xFF);
  EEPROM.write(0x09,0xFF);
  EEPROM.write(0x0A,0xFF);
  EEPROM.write(0x0B,0xFF);
  EEPROM.write(0x0c,0xFF);
  
  delay(1000);
  EEPROM.commit();
  EEPROM.end();
  delay(1000);
  Serial.println("");
  Serial.println("Done!");
}
#else
void setup() {
  Serial.begin(9600);
  EEPROM.begin(512);
  Serial.println("");
  Serial.println(char(EEPROM.read(0)));
  Serial.println(char(EEPROM.read(1)));
  Serial.println(char(EEPROM.read(2)));
  delay(1000);
  EEPROM.end();
  delay(1000);
  Serial.println("");
  Serial.println("Done!");
}

#endif
void loop() {
  // put your main code here, to run repeatedly:
}