void setup() {
  
  Serial.begin(250000); // setup serial

}

void loop() {
  
  Serial.println(analogRead(A0));
  //Serial.println(digitalRead(7));

  delay(1);

} 
