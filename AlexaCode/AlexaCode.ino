#include <ESP8266WiFi.h>
#include <RCSwitch.h>
#include "fauxmoESP.h"

#define WIFI_SSID "SSID"
#define WIFI_PASS "PASSWORD"
 
fauxmoESP alexawifi;
RCSwitch mySwitch = RCSwitch();
 
void wifi() {

/*
# WLAN SETUP
*/
    WiFi.mode(WIFI_STA);
    Serial.printf("Connecting to %s ", WIFI_SSID);
    
    WiFi.begin(WIFI_SSID, WIFI_PASS);
 
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(">");
        delay(200);
    } 
    Serial.println("");
    Serial.printf("Connected! SSID: %s, IP: %s\n", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());
}
 
void alexaAction(uint8_t device_id, const char * device_name, bool state) {
  Serial.print("Device: "); Serial.println(device_name); 
  Serial.print("State: ");
  Serial.println(device_id);
  
  if (state) {
    //turn on
  
    /*
    if(device_id == n) {
    Serial.println("device_name AN");
    // mySwitch.switchOn(learned_code);
    mySwitch.switchOn('a', 1, 1);
    delay(50);
    }
    */

    if(device_id == 0) {
    Serial.println("Device AN");
    
    mySwitch.switchOn('a', 1, 1);
    delay(50);
    }


    if(device_id == 1) {
    Serial.println("Device1 AN");
    mySwitch.switchOff('a', 1, 2);
    delay(50);
    }
    if(device_id == 2) {
    Serial.println("Device2 AN");
    
    mySwitch.switchOn('a', 1, 3);
    delay(50);
    }


  } 
  //turn off
  else {
    
    if(device_id == 0) {
    Serial.println("Device AUS");    
    mySwitch.switchOff('a', 1, 1);
    delay(50);
    }

    if(device_id == 1) {
    Serial.println("Device1 AUS");
    mySwitch.switchOff('a', 1, 2);
    delay(50);
    }
    
    if(device_id == 2) {
    Serial.println("Device2 AUS");
    mySwitch.switchOff('a', 1, 3);
    delay(50);
    }
}

}
 


void initDevices(){
    // Name will appear in alexa
    alexawifi.addDevice("AlexaCallName1"); //ID 0
    alexawifi.addDevice("AlexaCallName2"); //ID 1
    alexawifi.addDevice("AlexaCallName3"); //ID 2
    // alexawifi.addDevice("XXX");//ID n

    alexawifi.onMessage(alexaAction);
}

void setup() {

    Serial.begin(115200);
    Serial.println("Say 'Alexa, schalte <Gerät> an/aus'.");
    mySwitch.enableTransmit(0);

    wifi();
    initDevices();
  
} 
void loop() {
  alexawifi.handle();
}
