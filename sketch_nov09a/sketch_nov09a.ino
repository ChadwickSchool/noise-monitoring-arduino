#include <SPI.h>
#include <WiFiNINA.h>
#include <HttpClient.h>
#include "HTTPClient.h"

char ssid[] = "ChadwickStudent";   //  your network SSID (name)
char pass[] = "godolphins";        // your network password
String postData = "value1=4";      // test data value


WiFiClient client;                 // Initialize the client library              
IPAddress server(10,11,128,175);   //the IP Address of the server the Arduino will connect to 

 
int baseLine = 508;  //sound calibration value


int relativeSound;   //sound relative to thebaseline
int soundInput;      // raw sound input value

  
int sum = 0;
int count = 0;
double avg = 0;
int maxSound = 0;

// takes the absolute value of input
double absVal(double val) {
  if (val<0) {
    return -val;
  } else {
    return val;
  }
  
}

//resets the Arduino's connection to the server
void startConnection() {
 client.stop();
 Serial.println("stopped");
 client.connect(server,8000);
 Serial.println("reconnected");
}

//connects the Arduino to Wifi
void setup() {
    Serial.begin(9600);
    Serial.println("hi"); 
  
  while (WiFi.status() != WL_CONNECTED) {
      Serial.println("Not Connected to Wifi"); 
    WiFi.begin (ssid,pass); 
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("Bad");
    }
  }     

    Serial.println("Connected to wifi");
    Serial.println("\nStarting connection...");
    // if you get a connection, report back via serial:
    if (client.connect(server, 8000)) {
      Serial.println("connected");
    }
}

//measures the sound input to the Arduino, and sends the data to the server
void loop() { 
  // put your main code here, to run repeatedly:
   soundInput = analogRead(A0); // get the voltage of the sound detector is sending 
  relativeSound = abs(soundInput - baseLine); // find the relative 0 and how large the voltage spike above that line
  sum += relativeSound; // add the relative voltage to a sum
  maxSound = max(maxSound,relativeSound); // find the max sound with the max fucntion
  if (count >= 100) { // if it has looped 1000 times
    startConnection();
   if (sum <0) {
   }
    avg = absVal((double)sum / (double)count); // caculute the average
   client.println("GET /update-sheet?avg="+ (String)avg + "&max=" + (String)maxSound + " HTTP/1.1"); //send data to the server
 if (!client.connected()) {
  Serial.println("bad, Very Bad!"); //very bad to not be connected during this stage
 }
     Serial.println("sent");
   client.println(); 
    sum = 0; // reset values back down to 0
    count = 0;
    avg = 0;
    maxSound = 0;
  }
  count++;
  delay(1); //small delay for timing
}
