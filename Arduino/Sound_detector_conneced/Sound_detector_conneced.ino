
  int maxSound = 0;
  int baseLine = 508;


  int relativeSound;
  int soundInput;

  
  int sum = 0;
  int count = 0;
  double avg = 0;
  int maxSound = 0;

void setup() {
  
  Serial.begin(115200); // setup serial

}

void loop() {


  //get the voltage of the sound detector is sending 
  soundInput = analogRead(A0);

  //get the voltage of the sound detector is sending 
  // find the relative 0 and how large the voltage spike above that line
  // add the relative voltage to a sum.
  soundInput = analogRead(A0);
  relativeSound = abs(soundInput - baseLine);
  sum += relativeSound;

  maxSound = max(maxSound,relativeSound);

  sum += relativeSound;

  if (count == 1000) {
     avg = (double)sum / (double)count;
      
    // send post request here. print is for testing
    Serial.println(avg);
    sum = 0;
    count = 0;
    avg = 0;
    maxSound = 0;
  }

  count++;

  delay(1);

} 
