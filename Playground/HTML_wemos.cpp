#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>


const byte interruptPin = 5;
const byte sensePin = 4;
volatile uint8_t interruptCounter = 0;
uint8_t sensor_value = 0;
uint8_t minus = 0;


/* Set these to your desired credentials. */
const char *ssid = "Access poit";
const char *password = "";
int milisInterval = 200;
int count = 0;
ESP8266WebServer server(80);

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
 * connected to this access point to see it.
 */

 
void handleRoot() {


String html ="<!DOCTYPE html>";

html +="<style>";
html +="html {height: 100%; background: radial-gradient(rgb(50,50,50), rgb(40,40,40), rgb(20,20,20));}";

html +="h1 {display: block; margin:auto; font-family: Arial ; font-weight: bold; font-size: 2000%;color: white; text-align: center; position: relative;margin-top:0px;}";

html +="p1 {display: block; margin:auto; font-family: Arial ; font-weight: bold; font-size: 2500%;color: white; text-align: center; position: relative; margin-top:30px;}";

html +="button {display: block; margin:auto;height: 400px; width: 400px; font-family: Arial ;font-size: 800%; font-weight: bold; border-radius: 50%; outline-style: none; position:relative; margin-top:150 px; }";

html +="#dataVals { max-width: 400px; display: block; margin-top: 30px; }";
html +="</style>";





html +="</head>";
html +="<body>";
html +="<h1>Counter_value</h1>";
html +="<p1 id=\"sensor_value\"></p1>";
html +="<button onclick=zero()> Zero </button>";




html +="<script>";

html +="var changed = false;";

html +="function loadDoc() {";
html +="    var xhttp = new XMLHttpRequest();";
html +="    xhttp.onreadystatechange = function() {";
html +="        if (this.readyState == 4 && this.status == 200) {";
html +="        var obj = JSON.parse(this.responseText);";
html +="        document.getElementById(\"sensor_value\").innerHTML = obj.data[0].dataValue;";
html +="        }";
html +="    };";
html +="    xhttp.open(\"GET\", \"/data\", true);";
html +="    xhttp.send();";
html +="}";

html +="function zero(){";
html +=" zero = document.getElementById(\"sensor_value\").innerHTML;";
html +="}";

html +="}";

html +="var timedEvent = setInterval(function(){ loadDoc(); }, 200);";


html +="</script>";





html +="</body> </html>";

server.send(200, "text/html", html);

}







void getData() {   
   //This is a JSON formatted string that will be served. You can change the values to whatever like.
   //you can update multiple parameters of page like this
   // {"data":[{"dataValue":"1024"},{"dataValue":"23"}]} This is essentially what is will output you can add more if you like
  //LDRReading = analogRead(LDRPin);
  sensor_value = interruptCounter;
 
  String text2 = "{\"data\":[";
 
  text2 += "{\"dataValue\":\"";
  text2 += sensor_value;
  text2 += "\"}]}";
 
  server.send(200, "text/html", text2);
  count++;
}





void setup() {
  delay(200);
  //set interrupt pin as input
  pinMode(interruptPin, INPUT_PULLUP);
  pinMode(sensePin,INPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), handleInterrupt, FALLING);

 
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  server.on("/", handleRoot);
  server.on("/data", getData);
  server.begin();
}

void loop() {
  server.handleClient();
}





void handleInterrupt() {
 
  //If interrupt pin is HIGH
  //if sense pin is low incriment
  //else if low decriment
  if (digitalRead(interruptPin) == HIGH){
    //if HIGH incriment counter
    if (digitalRead(sensePin) == HIGH){
        interruptCounter++;
      }
   
   
   

    else{
        interruptCounter--;
      }

    }



  if (digitalRead(interruptPin) == LOW){
    //if HIGH incriment counter
    if (digitalRead(sensePin) == HIGH){
        interruptCounter--;
      }
   

    else{
        interruptCounter++;
      }
    }
}