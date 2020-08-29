/* Create a WiFi access point and provide a web server on it. */

#include <ESP8266WiFi.h>
#include "DNSServer.h"                  // Patched lib
#include <ESP8266WebServer.h>

const byte        DNS_PORT = 53;          // Capture DNS requests on port 53
IPAddress         apIP(192, 168, 4, 1);    // Private network for server
DNSServer         dnsServer;              // Create the DNS object
ESP8266WebServer  webServer(80);          // HTTP server

String responseHTML = "<!DOCTYPE html>"
  "<html lang=\"en\">"
  "<head>"
    "<meta charset=\"utf-8\">"
    "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"
    "<title>Relay Control</title>"
  "</head>"
  "<body>"
  "<p>Relay Test</p>"
  "</body>"
  "</html>";
  
String dbg = "";

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println('\n');

  // turn the LED on (HIGH is the voltage level)
  pinMode(D1, OUTPUT);
  digitalWrite(D1, LOW);

  // configure access point
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP("RelayControl"); // WiFi name

  // if DNSServer is started with "*" for domain name, it will reply with
  // provided IP to all DNS request
  dnsServer.start(DNS_PORT, "relay", apIP);

  // replay to all requests with same HTML
  webServer.onNotFound([]() {
    webServer.send(200, "text/html", responseHTML);
  });
  webServer.begin();
}

void loop() {
  dnsServer.processNextRequest();
  webServer.handleClient();
}
