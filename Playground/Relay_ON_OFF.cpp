/*
 * Control an LED from a web browser
 * Build to be run on an ESP8266
 * 
 * connect to the ESP8266 AP then
 * use web broswer to go to 192.168.4.1
 * 
 */
 
 
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>        // Include the mDNS library
const char WiFiPassword[] = "12345678";
const char AP_NameChar[] = "RelayControl" ;

 
WiFiServer server(80);
 
String header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";

String html_1 = "<!DOCTYPE html>\
                <html>\
                  <head>\
                    <title>Relay Control</title>\
                  </head>\
                  <body>\
                  <div id='main'>\
                  <h2>Relay Control</h2>";

String html_2 = "<form id='F1' action='ON'>\
                  <input class='button' type='submit' value='ON' >\
				  button {display: block; margin:auto;height: 400px; width: 400px; font-family: Arial ;font-size: 800%; font-weight: bold; border-radius: 50%; outline-style: none; position:relative; margin-top:150 px; }\
                </form><br>";

String html_3 = "<form id='F2' action='OFF'>\
                 <input class='button' type='submit' value='ON' >\
				  button {display: block; margin:auto;height: 400px; width: 400px; font-family: Arial ;font-size: 800%; font-weight: bold; border-radius: 50%; outline-style: none; position:relative; margin-top:150 px; }\
                </form><br>";

String html_4 = "</div></body></html>";
 
String request = "";
int Relay_Pin = D1;
 
void setup() 
{
  Serial.begin(115200);
  delay(10);
  Serial.println('\n');

  pinMode(Relay_Pin, OUTPUT); 

  Serial.println(WiFi.softAP(AP_NameChar, WiFiPassword) ? "Ready" : "Failed!");

  

  IPAddress myIP = WiFi.softAPIP();
  Serial.println(myIP);

  /* Start the mDNS responder for esp8266.local*/
  if (!MDNS.begin("relay",myIP)) 
  {             
    Serial.println("Error setting up MDNS responder!");
  }
  Serial.println("mDNS responder started");
 server.begin();
} 
 
void loop() 
{
 
    // Check if a client has connected
    WiFiClient client = server.available();

    if (!client)
    {
      return;
    }
 
    // Read the first line of the request
    request = client.readStringUntil('\r');
 
    if( request.indexOf("ON") > 0 )  
    { 
      digitalWrite(Relay_Pin, HIGH);  
    }
    else if ( request.indexOf("OFF") > 0 ) 
    { 
      digitalWrite(Relay_Pin, LOW);
    }
    else
    {
      /* do nothing */
    }
    
 
    client.flush();
 
    client.print( header );
    client.print( html_1 );
    client.print( html_2 );
    client.print( html_3 );
    client.print( html_4);
 
    delay(5);

  // The client will actually be disconnected when the function returns and 'client' object is detroyed
 
}