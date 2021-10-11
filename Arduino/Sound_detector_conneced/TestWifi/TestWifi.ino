#include <SPI.h>
#include "ESP8266WiFi.h"
 
char ssid[] = "ChadwickStudent";          //  your network SSID (name)
char pass[] = "godolphins";   // your network password
 
int status = WL_IDLE_STATUS;

// Initialize the client library
WiFiClient client;

void setup() {
  Serial.begin(9600);
  Serial.println("Attempting to connect to WPA network...");
  Serial.print("SSID: ");
  Serial.println(ssid);

  status = WiFi.begin(ssid, pass);
  if ( status != WL_CONNECTED) {
    Serial.println("Couldn't get a wifi connection");
    // don't do anything else:
    while(true);
  }
  else {
    Serial.println("Connected to wifi");
    Serial.println("\nStarting connection...");
    // if you get a connection, report back via serial:
    if (client.connect("script.google.com", 80)) {
      Serial.println("connected");
      // Make a HTTP request:
      client.println("POST /macros/s/AKfycbzCOBoAl9rktpOCaPJ5BNWc1PbexzaN_JYhaMlChnqa5bbD7-cAaxv-QCeUkieKrf5G/exec?value1=3 HTTP/1.1");
      client.println();
    } 
  }
}

void loop() {
  // put your main code here, to run repeatedly:

} 
