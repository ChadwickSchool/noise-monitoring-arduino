  int baseLine = 508;

  int relativeSound;
  int soundInput;

  
  int sum = 0;
  int count = 0;
  double avg = 0;
  int maxSound = 0;

  String severIP = "10.11.2.76:8000";
  String httpRequest = "";
  
void setup() {
  Serial.begin(1000000); // setup serial
}

void loop() {
  soundInput = analogRead(A0); // get the voltage of the sound detector is sending 
  relativeSound = abs(soundInput - baseLine); // find the relative 0 and how large the voltage spike above that line
  sum += relativeSound; // add the relative voltage to a sum
  maxSound = max(maxSound,relativeSound); // find the max sound with the max fucntion
  if (count == 1000) { // if it has looped 1000 times
    avg = (double)sum / (double)count; // caculute the avrage
    httpRequest = "http://" + severIP + "/update-sheet?" + "avg=" + (String)avg + "&max=" + (String)maxSound; // format data into a sendable form
    sum = 0; // reset values back down to 0
    count = 0;
    avg = 0;
    maxSound = 0;
  }
  count++;
  delay(1);
} 
