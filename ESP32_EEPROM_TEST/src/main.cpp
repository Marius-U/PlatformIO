#include <Arduino.h>
#include <EEPROM.h>


#if 0
void setup() {
  Serial.begin(9600);
  EEPROM.begin(512);
  EEPROM.write(0,'A');
  EEPROM.write(1,'B');
  EEPROM.write(2,'C');
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