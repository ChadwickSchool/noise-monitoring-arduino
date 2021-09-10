//detects if ambient sound is above a certain level, and if so, triggers a LED
//wire color order: yellow, purple, orange, brown

#undef int
#undef abs
#undef double
#undef float
#undef round
#include <SPI.h> 
#include <WiFiNINA_Generic.h>  
#include "arduino_secrets.h" 

const int pinAdc = A0;

///////////////////////////////
///      EDIT THIS STUFF     //
///////////////////////////////

char devid[] = "v45469F2B40A60FB";  // THIS IS THE DEVICE ID FROM PUSHINGBOX

int del = 300; // Amount of seconds delay between posting to google docs.

char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;                 // your network key Index number (needed only for WEP)
int ranNum = 0;
String Info;
int maxNoise = 0;
int maxTime;

///////////////////////////////
//       DONE EDITING        //
///////////////////////////////

int status = WL_IDLE_STATUS;

char postmsg[100];
int k = 0;
int temp_av = 0;
char server[] = "api.pushingbox.com";
WiFiClient client;

void setup()
{

  Serial.begin(9600);

  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Comm2unication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv != "1.0.0") {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);                   // print the network name (SSID);

    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    // wait 10 seconds for connection:
    delay(10000);
    Serial.print("Testing server connection...");
  }
  if (client.connect(server, 80)) {
    Serial.println("connected to server.");
    Serial.println("");
  }
  // printWifiStatus();                        // you're connected now, so print out the status

  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  Serial.begin(9600);

  pinkOn();
  delay(3000);
}

//place and length information coordinated with disruption report
String disruptionPlace = "A1";
double disruptionLength = 0.0;

//gradient mode allows the colors to switch more smoothly (priority over rainbow mode and gradient rainbow mode)
boolean activateGradientMode = true; //setting

//gradient rainbow, flashes through colors with gradient (priority over rainbow mode)
boolean activateRainbowGradientMode = false; //setting
double rainbowGradientModeDelaySec = 0.1; //refine
int rainbowGradientModeDelay = int(rainbowGradientModeDelaySec * 1000);

//rainbow mode flashes through all colors with a set delay
boolean activateRainbowMode = false; //setting
double rainbowModeDelaySec = 1.0; //refine
int rainbowModeDelay = int(rainbowModeDelaySec * 1000);

//last reading of sound sensor, used for reading smoothing
int lastSum = 0;

//different volumes at which light changes (green, yellow, red)
int volumeLevelOne = 400; //refine
int volumeLevelTwo = 600; //refine
int volumeLevelThree = 700; //refine

//minimum amount of time a light will stay on for (flickering prevention)
double minLightFlashSec = 2.0; //refine
int minLightFlash = int(minLightFlashSec * 100);

//delay values set to minimum light flash when triggered
int greenDelay = 0;
int yellowDelay = 0;
int redDelay = 0;

//pins from which LED receives color info, RGB
int redPin = 10;
int greenPin = 11;
int bluePin = 12;

void loop()
{

  //ignored if gradient mode not activated
  if (activateGradientMode) {
    gradient();

    //ignored if rainbow gradient mode not activated
  } else if (activateRainbowGradientMode) {

    rainbowGradient();

    //ignored if rainbow or rainbow gradient mode not activated
  } else if (activateRainbowMode) {

    rainbow();

    //if all else fails, activate the default step lights mode
  } else {

    stepLights();
  }

}

void stepLights() {

  while (true) {

    //set sum to rough sensor reading
    long sum = 0;
    for (int i = 0; i < 32; i++)
      sum += analogRead(pinAdc);

    sum >>= 5;

    //smooth sound sensor readings
    double filtered = (0.2 * sum) + (0.8 * lastSum);

    //if volume greater than level three
    if (sum >= volumeLevelThree)
    {
      //turn on red light
      redOn();
      redDelay = minLightFlash;

      //if volume between level two and level three
    } else if (sum >= volumeLevelTwo && sum < volumeLevelThree)
    {
      //turn on yellow light
      if (redDelay <= 0) {
        yellowOn();
        yellowDelay = minLightFlash;
      }

      // if volume between level one and level two
    } else if (sum >= volumeLevelOne && sum < volumeLevelTwo)
    {
      //turn on green light
      if (yellowDelay <= 0 && redDelay <= 0) {
        greenOn();
        greenDelay = minLightFlash;
      }

      // if volume less than level one
    } else {
      //otherwise, turn off
      if (greenDelay <= 0 && yellowDelay <= 0 && redDelay <= 0) {
        lightOff();
      }
    }

    //print smoothed sensor reading to graph
    //Serial.println(sum);

    delay(10);

    //sets last sum for sensor smoothing next loop
    lastSum = filtered;

    delayLight();

  }

}

//changes light delay values accordingly
void delayLight() {

  //decrement the green light delay if it is a value greater than 0
  if (greenDelay > 0) {
    greenDelay--;
  }

  //decrement the yellow light delay if it is a value greater than 0
  if (yellowDelay > 0) {
    yellowDelay--;
  }

  //decrement the red light delay if it is a value greater than 0
  if (redDelay > 0) {
    redDelay--;

    //increment disruption length while red delay is greater than 0
    disruptionLength = disruptionLength + 0.01;

    //after red light delay runs out, send a report
    if (redDelay <= 0) {
      Serial.println("Sending report to pushingbox.com...");
      sendReport();
    }

  }
}

//disco lights ¯\_(ツ)_/¯
void rainbow() {
  while (true) {

    redOn();
    delay(rainbowModeDelay);

    orangeOn();
    delay(rainbowModeDelay);

    yellowOn();
    delay(rainbowModeDelay);

    greenOn();
    delay(rainbowModeDelay);

    aquaOn();
    delay(rainbowModeDelay);

    blueOn();
    delay(rainbowModeDelay);

    pinkOn();
    delay(rainbowModeDelay);

    whiteOn();
    delay(rainbowModeDelay);

  }
}

//gradient disco lights ¯\_(ツ)_/¯
void rainbowGradient() {
  int r = 0;
  int g = 0;
  int b = 0;
  while (true) {

    for (int red = 0; red <= 255; red++) {
      r = red;
      setColor(r, 0, 0);
      delay(rainbowGradientModeDelay);
    }

    for (int green = 0; green <= 255; green++) {
      g = green;
      setColor(r, g, 0);
      delay(rainbowGradientModeDelay);
    }

    for (int blue = 0; blue <= 255; blue++) {
      b = blue;
      setColor(r, g, b);
      delay(rainbowGradientModeDelay);
    }

  }
}

//switches the colors more smoothly as volume increases/decreases
void gradient() {
  int r = 0;
  int g = 0;

  int changeFactor = 25;
  while (true) {

    //set sum to rough sensor reading
    long sum = 0;
    for (int i = 0; i < 32; i++)
      sum += analogRead(pinAdc);

    sum >>= 5;

    //smooth sound sensor readings
    double filtered = (0.2 * sum) + (0.8 * lastSum);

    //if volume greater than level three
    if (sum >= volumeLevelThree)
    {

      if (r < changeFactor * 10)
        r = r + changeFactor;

      if (g > 0)
        g = g - changeFactor;

      redDelay = minLightFlash;

      //if volume between level two and level three
    } else if (sum >= volumeLevelTwo && sum < volumeLevelThree)
    {

      if (redDelay <= 0) {

        if (r < changeFactor * 10)
          r = r + changeFactor;

        if (g < changeFactor * 10)
          g = g + changeFactor;

        yellowDelay = minLightFlash;

      }

      // if volume between level one and level two
    } else if (sum >= volumeLevelOne && sum < volumeLevelTwo)
    {

      if (yellowDelay <= 0 && redDelay <= 0) {

        if (r > 0)
          r = r - changeFactor;

        if (g < changeFactor * 10)
          g = g + changeFactor;

        greenDelay = minLightFlash;

      }

      // if volume less than level one
    } else {
      if (greenDelay <= 0 && yellowDelay <= 0 && redDelay <= 0) {
        //otherwise, turn off

        r = 0;
        g = 0;
        lightOff();
      }
    }

    if (sum >= volumeLevelOne)
      setColor(changeFactor * 10 - r, changeFactor * 10 - g, 255);

    //print smoothed sensor reading to graph
    //Serial.println(sum);

    delay(10);

    //sets last sum for sensor smoothing next loop
    lastSum = filtered;

    delayLight();

  }

}

//turn on red light
void redOn() {
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, HIGH);
}

//turn on green light
void greenOn() {
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, HIGH);
}

//turn on blue light
void blueOn() {
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, LOW);
}

//turn on yellow light
void yellowOn() {
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, HIGH);
}

//turn on pink light
void pinkOn() {
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, LOW);
}

//turn on aqua light
void aquaOn() {
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
}

//turn on white light
void whiteOn() {
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
}

//turn off light
void lightOff() {
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, HIGH);
}

//turn on orange light
void orangeOn() {
  setColor(0, 90, 255);
}

//sets color to rgb value, for use in gradient mode
void setColor(int red, int green, int blue)
{
#ifdef COMMON_ANODE
  red = 255 - red;
  green = 255 - green;
  blue = 255 - blue;
#endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

//send report message with time and place information
//client.print("Library_section:‎‎_" + disruptionPlace + "_was_disrupted_for:_" + disruptionLength + "_seconds.");
void sendReport() {

  // Post to Google Form.............................................
  if (client.connect(server, 80))
  {
    k = 0;
    Serial.println("Connected to google form.");
    client.print("GET /pushingbox?devid=v45469F2B40A60FB&status=");

    Serial.println("Attempting to send message: Library_section‎‎_" + disruptionPlace + "_was_disrupted_for_" + (int) disruptionLength + "_seconds");
    client.print("Library_section_" + disruptionPlace + "_was_disrupted_for_" + (int) disruptionLength + "_seconds");

    //reset disruption length
    disruptionLength = 0.0;

    client.print(" HTTP/1.1\r\n");
    client.print("Host: api.pushingbox.com\r\n\r\n");
    client.println("Connection: close");
    client.println();
    Serial.println(postmsg);
    Serial.println("Host: api.pushingbox.com");
    Serial.println("Connection: close");
    Serial.println();
    delay(1000);
    client.stop();
    ranNum++;
  }
  delay(10000);

  if (!client.connected())
  {
    Serial.println();
    Serial.println("Disconnecting from pushingbox.com.");
    client.stop();
    k == 1;
    return;
  }

}
