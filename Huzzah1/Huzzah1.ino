/* Huzzah . 
 
Connect one end of FSR to power, the other end to Analog 0.
Then connect one end of a 10K resistor from Analog 0 to ground 
 
For more information see www.ladyada.net/learn/sensors/fsr.html */

#include <ESP8266WiFi.h>
 
const char* ssid     = "MHacks";
const char* password = "Walmart!";
 
const char* host = "www.adafruit.com";

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

  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}

 
void loop(void) {

  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  
  // We now create a URI for the request
  String url = "/testwifi/index.html";
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(10);
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection");





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
