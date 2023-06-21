/**************************************************************************
 
Written by Divija Durga, with help from the contributions of the open source community. 

 **************************************************************************/

#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>
#include <Servo.h>
const char DEVICE_LOGIN_NAME[] = ""; //get info from Arduino Cloud

const char SSID[] = "";                          // Network SSID (name)
const char PASS[] = "";                   // Network password (use for WPA, or use as key for WEP)
const char DEVICE_KEY[] = "";  // Secret device password get from Arduino Cloud

void onServo1Change();

CloudLight servo1; //bool also works

void initProperties() {

  ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME);
  ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);
  ArduinoCloud.addProperty(servo1, READWRITE, ON_CHANGE, onServo1Change);
}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);
Servo s1;

void setup() {
  
  Serial.begin(9600);
  s1.write(0);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500);

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
 */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
  s1.attach(0);
}

void loop() {
  ArduinoCloud.update();
  // Your code here
}



void onServo1Change() {
  if (servo1) {
    s1.write(180);
    delay(1000);
    s1.write(0);
    servo1=0;
    /* 
    adjust for style of kettle. The tab of my kettle comes up on its own once it is hot, 
    so my servo needs to reset to its original position. A classic button, switch or slider
    will not work
    */ 
  }



}
