#include "userconfig.h"
#include <ESP8266WiFi.h>
WiFiClient espClient; 
//  Alexa
#include "fauxmoESP.h"
fauxmoESP alexawifi;
// 433 Mhz
#include <RCSwitch.h>
RCSwitch mySwitch = RCSwitch();
// IR 
#include <IRremoteESP8266.h>
#include <IRsend.h>
IRsend irsend(IR_connected_pin); 
//mqtt
#include <PubSubClient.h> 
PubSubClient client(espClient);
 
void setup_wifi() { 
    delay(10); 
    // We start by connecting to a WiFi network 
    Serial.println(); 
    Serial.print("Connecting to "); 
    Serial.println(ssid); 
    WiFi.begin(ssid, password); 
    while (WiFi.status() != WL_CONNECTED) { 
      delay(500); 
      Serial.print("."); 
    } 
    randomSeed(micros()); 
    Serial.println(""); 
    Serial.println("WiFi connected"); 
    Serial.println("IP address: "); 
    Serial.println(WiFi.localIP()); 
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
        callcase48();
        delay(50);
      }
      if(device_id == 1) {
        Serial.println("Device1 AN");
        callcase50();
        delay(50);
      }
      if(device_id == 2) {
        Serial.println("Calling case 52 now");
        callcase52();
        Serial.println("called case 52");
        delay(50);
      }
    } 
    //turn off
    else {
      
      if(device_id == 0) {
        Serial.println("Device AUS");    
        callcase49();
        delay(50);
      }
  
      if(device_id == 1) {
        Serial.println("Device1 AUS");
        callcase51();
        delay(50);
      }
      
      if(device_id == 2) {
        Serial.println("Device2 AUS");
        callcase53();
        delay(50);
      }
  }
  
  }


void initDevices(){
    // Name will appear in alexa
    alexawifi.addDevice("Küchenlicht"); //ID 0
    alexawifi.addDevice("Schwarzlicht"); //ID 1
    alexawifi.addDevice("Sofalicht"); //ID 2
    // alexawifi.addDevice("XXX");//ID n

    alexawifi.onMessage(alexaAction);
}

void setup() {
    Serial.begin(115200);
    setup_wifi();
    #ifdef mqtt
      setupmqtt();
    #endif
    #ifdef RC433mhz
      setupRC();
    #endif
    #ifdef IR
      setupIR();
    #endif
    Serial.println("Say 'Alexa, schalte <Gerät> an/aus'.");
    mySwitch.enableTransmit(mqtt_connected_pin);
    initDevices();
} 
void loop() {
  alexawifi.handle();
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
