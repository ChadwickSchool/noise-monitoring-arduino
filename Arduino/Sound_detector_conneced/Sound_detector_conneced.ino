  int baseLine = 508;

  int relativeSound;
  int soundInput;

  
  int sum = 0;
  int count = 0;
  double avg = 0;
  int maxSound = 0;

  String post = "/macros/s/AKfycbzCOBoAl9rktpOCaPJ5BNWc1PbexzaN_JYhaMlChnqa5bbD7-cAaxv-QCeUkieKrf5G/exec?";
  String postWithData = "";
  
void setup() {
  
  Serial.begin(115200); // setup serial

}

void loop() {

  // get the voltage of the sound detector is sending 
  // find the relative 0 and how large the voltage spike above that line
  // add the relative voltage to a sum.
  soundInput = analogRead(A0);
  relativeSound = abs(soundInput - baseLine);
  sum += relativeSound;

  maxSound = max(maxSound,relativeSound);

  if (count == 50) {
     avg = (double)sum / (double)count;
      
    //Send post request here. print is for testing
    //Serial.println(avg);
    //Serial.println(maxSound);
    // in to put data as the value 1 2 
    // script.google.com/macros/s/AKfycbzCOBoAl9rktpOCaPJ5BNWc1PbexzaN_JYhaMlChnqa5bbD7-cAaxv-QCeUkieKrf5G/exec? value1=3&value2=4&value3=6
    postWithData = post + "value1=" + (String)avg + "&value2=" + (String)maxSound;
    sum = 0;
    count = 0;
    avg = 0;
    maxSound = 0;

  }

  //Serial.println(relativeSound);

  count++;

  delay(1);

} 
