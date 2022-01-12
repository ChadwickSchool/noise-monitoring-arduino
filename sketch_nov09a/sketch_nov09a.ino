#include <SPI.h>
#include <WiFiNINA.h>
#include <HttpClient.h>
#include "HTTPClient.h"
//#include "ESP8266WiFi.h"

char ssid[] = "ChadwickStudent";          //  your network SSID (name)
char pass[] = "godolphins";   // your network password
String postData = "value1=4";
// Initialize the client library
WiFiClient client;
IPAddress server(10,11,0,57);

int baseLine = 508; 

int relativeSound;
int soundInput;

  
int sum = 0;
int count = 0;
double avg = 0;
int maxSound = 0;

//int[] measureSound() {
 // return [0];
//}
double absVal(double val) {
  if (val<0) {
    return -val;
  } else {
    return val;
  }
  
}
void startConnection() {
 client.stop();
 Serial.println("stopped");
 client.connect(server,8000);
 Serial.println("reconnected");
}
void setup() {
//  HttpClient http(client);
 // HTTPClient http;
    Serial.begin(9600);
    Serial.println("hi"); 
  
/*  if (status == WL_CONNECTED) {
    Serial.println("Already Connected"); 
  } else {
    Serial.println("Not Already Connected"); 
  }
  
   

  Serial.println("Attempting to connect to WPA network...");
  Serial.print("SSID: ");
  Serial.println(ssid);
  
  status = WiFi.begin(ssid, pass);
  Serial.println(status);
  if (status != WL_CONNECTED) {
    Serial.println("Couldn't get a wifi connection");
    // don't do anything else:
    while(true);
  } 
  else {
  */
  while (WiFi.status() != WL_CONNECTED) {
      Serial.println("Not Connected to Wifi"); 
    WiFi.begin (ssid,pass); 
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("Bad");
    }
  }     
  //http://10.11.2.76:8000/update-sheet?avg=67&max=78


    Serial.println("Connected to wifi");
    Serial.println("\nStarting connection...");
    // if you get a connection, report back via serial:
    if (client.connect(server, 8000)) {
      Serial.println("connected");
  /*    // Make a HTTP request:
      //client.println("GET /macros/s/AKfycbwbWCePDN1JfOb7qBkFjAIIqerS5dISDM41FLeW9Vx13pkJIfbBTbDCQAKHrNd5mBVo/exec?value1=4 HTTP/1.1");
      client.println("GET /update-sheet?avg=117&max=526 HTTP/1.1");
     // client.println("Host: script.google.com");
 //     client.println("Host: script.google.com");
  //    client.println("Connection: close");
      client.println(); 
  //    Serial.println(client.read());
 
  }
 // hwhile
 */
    }

}

void loop() {
  // client.connect(server,8000);
  //startConnection();
  // put your main code here, to run repeatedly:
   /*  if (client.available()) {
      Serial.print(client.read());
     } 
       delay(100);
       */
   soundInput = analogRead(A0); // get the voltage of the sound detector is sending 
  relativeSound = abs(soundInput - baseLine); // find the relative 0 and how large the voltage spike above that line
  sum += relativeSound; // add the relative voltage to a sum
 // Serial.println(sum);
  if (relativeSound<0) {
   // Serial.println("Negative Sound! SOUND the Alarm!");
  } 
  maxSound = max(maxSound,relativeSound); // find the max sound with the max fucntion
  if (count >= 100) { // if it has looped 1000 times
    startConnection();
   if (sum <0) {
  //  Serial.println("WAHHH!");
   }
    avg = absVal((double)sum / (double)count); // caculute the avrage
   client.println("GET /update-sheet?avg="+ (String)avg + "&max=" + (String)maxSound + " HTTP/1.1");
 if (!client.connected()) {
  Serial.println("bad, Very Bad!");
 }
 //  client.println("Connection: Keep-Alive"); 
     Serial.println("sent");
     //client.println("Connection: close");
   client.println(); 
    sum = 0; // reset values back down to 0
    count = 0;
    avg = 0;
    maxSound = 0;
  }
  count++;
  delay(1);
           // Make a HTTP request:
      //client.println("GET /macros/s/AKfycbwbWCePDN1JfOb7qBkFjAIIqerS5dISDM41FLeW9Vx13pkJIfbBTbDCQAKHrNd5mBVo/exec?value1=4 HTTP/1.1");

     // client.println("Host: script.google.com");
 //     client.println("Host: script.google.com");
  //    client.println("Connection: close");
      
      
}
