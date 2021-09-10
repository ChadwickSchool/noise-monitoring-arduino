void setup() {
  
  Serial.begin(9600); // setup serial

}

void loop() {
  
  Serial.println(analogRead(A0));
  //Serial.println(digitalRead(7));

  delay(100);

} 
