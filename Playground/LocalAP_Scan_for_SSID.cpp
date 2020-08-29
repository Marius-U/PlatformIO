#include <FS.h>                   //this needs to be first, or it all crashes and burns...
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager

void setup() {

  Serial.begin(115200);
  Serial.println();

  //WiFiManager

  WiFiManager wifiManager;

  //reset settings - for testing
  wifiManager.resetSettings();

  IPAddress _ip = IPAddress(192, 168, 1, 35);
  IPAddress _gw = IPAddress(192, 168, 1, 254);
  IPAddress _sn = IPAddress(255, 255, 255, 0);

  wifiManager.setSTAStaticIPConfig(_ip, _gw, _sn);
  if (!wifiManager.autoConnect("WemosAP", "ConfigureMe")) {
    Serial.println("failed to connect, we should reset and see if it connects");
    delay(3000);
    ESP.reset();
    delay(5000);
  }
  //if you get here you have connected to the WiFi
  Serial.println("connected...yeey :)");
  Serial.println("local ip");
  Serial.println(WiFi.localIP());
}
void loop() {
}