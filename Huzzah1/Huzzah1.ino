#include <CountingStream.h>
#include <Xively.h>
#include <XivelyClient.h>
#include <XivelyDatastream.h>
#include <XivelyFeed.h>
#include <ESP8266WiFi.h>
#include <HttpClient.h>

const int PRESSURE_THRESHOLD = 100;

const char* ssid     = "MHacks";
const char* password = "Walmart!";
 
/////////////////////////////////  
const int analogInPin = A0;  // Analog input pin that sensors is attached to (DEFAULT=A2)  
int readingDelay = 10;  // Delay between each reading (DEFAULT=10)  
int readingsPerSample = 10;  // Number of reaings per sample / loop (DEFAULT=10)  
boolean singleRead = false;  // Series of readings (False) or single reading (TRUE) (DEFAULT=FALSE)  
boolean enableVibes = true;  // LED  
int numberOfVibrators = 3;
const int vibratePins[] = {5,4,3};
/////////////////////////////////  
    

int analogReading;     // the analog reading from the FSR resistor divider

//huzzah 1
char const* xivelyKey1 = "m83CbEND8mduhY3YjZCUCmbQCvLvzyLrx3S2s9NAT5BTIjQd";
int FEED1 = 485777785;
char pressureStream[] = "pressure";

XivelyDatastream datastream1[] = {
  XivelyDatastream(pressureStream, strlen(pressureStream), DATASTREAM_INT),
};
XivelyFeed huzzah1(FEED1, datastream1, 1);


//huzzah 2
char const* xivelyKey2 = "3o0HH47WfmHdyEn2xpj9kwnCaMGueK1K7HA304QvmWzHcAvb";
int FEED2 = 838460654;

XivelyDatastream datastream2[] = {
  XivelyDatastream(pressureStream, strlen(pressureStream), DATASTREAM_INT),
};
XivelyFeed huzzah2(FEED2, datastream2, 1);


XivelyFeed selfFeed = huzzah1;
XivelyFeed pairFeed = huzzah2;
char const* selfXivelyKey = xivelyKey1;
char const* pairXivelyKey = xivelyKey2;
#define SELF_FEED_ID = FEED1
#define PAIR_FEED_ID = FEED2

WiFiClient client;
XivelyClient xivelyclient(client);

// XivelyFeed selfFeed = huzzah2;
// XivelyFeed pairFeed = huzzah1;
// char const* selfXivelyKey = xivelyKey2;
// char const* pairXivelyKey = xivelyKey1;
// #define FEED_ID = FEED2
// #define PAIR_FEED_ID = FEED1

void wifiSetup(void) {
  // Serial.print("Connecting to ");
  // Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    // Serial.print(".");
  }
 
  // Serial.println("");
  // Serial.println("WiFi connected");  
  // Serial.println("IP address: ");
  // Serial.println(WiFi.localIP());
}

void vibrateWithWait(int vibeTime) {
    // Serial.print("Initiating vibration");
    // Serial.println();
    for (int i = 0; i < numberOfVibrators ; i++) {
      digitalWrite(vibratePins[i], HIGH);
    }  
    // delay(vibeTime);
}

void disableVibrators(void) {
  // Serial.print("Turning vibrate off");
  //   Serial.println();
    for (int i = 0; i < numberOfVibrators ; i++) {
      digitalWrite(vibratePins[i], LOW);
    }  
}

int readAnalog(void) {
  analogReading = analogRead(analogInPin);  

  // Serial.print("Analog reading = ***************************************"); //
  Serial.println(analogReading);     // the raw analog reading
  // Serial.println();

  return analogReading;
}

int analogLevel(int analog) {
  //returns 1 for vibrate and 0 for don't vibrate
  if (analogReading < PRESSURE_THRESHOLD) {
    return 1;
  }
  else {
    return 0;
  }
}

int updateSelfPressure(void) {
  // int pressureBool = analogLevel(readAnalog());
  selfFeed[0].setInt(readAnalog());

  // Serial.print("Read sensor value ");
  // Serial.println(selfFeed[0].getInt());

  // Serial.println("Uploading it to Xively");
  int ret = xivelyclient.put(selfFeed, selfXivelyKey);
  // Serial.print("xivelyclient.put returned ");
  // Serial.println(ret);
  // Serial.println("");

}

int pairPressed(void) {
  //returns 0 if pair isnt pressed and 1 if it is pressed
  int getReturn = xivelyclient.get(pairFeed, pairXivelyKey);    //get data from xively
  if(getReturn > 0){
    // Serial.println("Pressure Datastream");
    // Serial.println(pairFeed[0].getInt());
    return pairFeed[0].getInt();
  } 
  else {
    // Serial.println("HTTP Error");
    // Serial.println(getReturn);
  }
}


void setup(void) {
  Serial.begin(9600);   
  for (int i = 0; i < numberOfVibrators ; i++) {
    pinMode(vibratePins[i], OUTPUT);
  }
 wifiSetup();
}


void loop(void) {
  
  updateSelfPressure();

  if (pairPressed() < PRESSURE_THRESHOLD) {
    vibrateWithWait(10);
  }
  else {
    disableVibrators();
  }

  // delay(1000);
} 
