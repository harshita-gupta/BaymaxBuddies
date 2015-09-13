int fsrPin = 1;     // the FSR and 10K pulldown are connected to a0
int fsrReading;     // the analog reading from the FSR resistor divider
 
void setup(void) {
  // We'll send debugging information via the Serial monitor
  Serial.begin(9600); 
  pinMode(12, OUTPUT);  
}
 
void loop(void) {
  fsrReading = analogRead(fsrPin);  
 
  Serial.print("Analog reading = ");
  Serial.print(fsrReading);     // the raw analog reading
 
  // We'll have a few threshholds, qualitatively determined
  if (fsrReading < 1) 
  {
    Serial.println(" - No pressure");
    digitalWrite(12, LOW);
  } 
  else if (fsrReading > 430) 
  {
    Serial.println(" - Light touch");
    digitalWrite(12, LOW);
  } 
  else if (fsrReading > 420) 
  {
    Serial.println(" - Light squeeze");
    digitalWrite(12, LOW);
  } 
  else if (fsrReading > 410) 
  {
    Serial.println(" - Medium squeeze");
    digitalWrite(12, LOW);
  } 
  else 
  {
    Serial.println(" - Big squeeze");
    digitalWrite(12, HIGH);
    Serial.println("1");
  }
  delay(0);
} 
