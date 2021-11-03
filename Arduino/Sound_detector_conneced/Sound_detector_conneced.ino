  int baseLine = 508;

  int relativeSound;
  int soundInput;

  
  int sum = 0;
  int count = 0;
  double avg = 0;
  int maxSound = 0;

  // value1=5&value2=512&value3=560
  //https://script.google.com/macros/s/AKfycbwbWCePDN1JfOb7qBkFjAIIqerS5dISDM41FLeW9Vx13pkJIfbBTbDCQAKHrNd5mBVo/exec?value1=5&value2=512
  String post = "/macros/s/AKfycbwbWCePDN1JfOb7qBkFjAIIqerS5dISDM41FLeW9Vx13pkJIfbBTbDCQAKHrNd5mBVo/exec?";
  String postWithData = "";
  
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
    postWithData = post + "value1=" + (String)avg + "&value2=" + (String)maxSound; // format data into a sendable form
    sum = 0; // reset values back down to 0
    count = 0;
    avg = 0;
    maxSound = 0;
  }
  count++;
  delay(1);
} 
