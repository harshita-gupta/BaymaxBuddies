/* Huzzah . 
 
Connect one end of FSR to power, the other end to Analog 0.
Then connect one end of a 10K resistor from Analog 0 to ground 
 
For more information see www.ladyada.net/learn/sensors/fsr.html */

int numberOfVibrators = 1;
int vibratePins[] = {2};
 
//char analogPin = AO;     // the FSR and 10K pulldown are connected to a0
int analogReading;     // the analog reading from the FSR resistor divider

void setup(void) {
  // We'll send debugging information via the Serial monitor
  Serial.begin(9600);   
  for (int i = 0; i < numberOfVibrators ; i++) {
    pinMode(vibratePins[i], OUTPUT);
  }

}
 
void loop(void) {

  for (int i = 0; i < numberOfVibrators ; i++) {
    digitalWrite(vibratePins[i], HIGH);
  }

//  digitalWrite(2, HIGH);
  analogReading = analogRead(A0);  
 
  Serial.print("Analog reading = ");
  Serial.print(analogReading);     // the raw analog reading
 
  // We'll have a few threshholds, qualitatively determined
  if (analogReading < 1) 
  {
    Serial.println(" - No pressure");
  } 
  else if (analogReading > 600) 
  {
    Serial.println(" - Light touch");
  } 
  else if (analogReading > 560) 
  {
    Serial.println(" - Light squeeze");
  } 
  else if (analogReading > 545) 
  {
    Serial.println(" - Medium squeeze");
  } 
  else 
  {
    Serial.println(" - Big squeeze");
  }
  delay(1000);
} 
