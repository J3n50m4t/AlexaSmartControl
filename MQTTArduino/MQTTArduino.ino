#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "userconfig.h"

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void setup() {
  // Initialize the BUILTIN_LED pin as an output while debugging
       
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void setup_wifi() {
// lange Deco leiste
  pinMode(4, OUTPUT);
  //lampions
  pinMode(0, OUTPUT);
  //Vase
  pinMode(14, OUTPUT);

  delay(10);
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
  WiFi.mode(WIFI_STA);
  Serial.println("WiFi.Mode set to STA");
}

void callback(char* topic, byte* payload, unsigned int length) {
  
  
  switch ((char)payload[0])
  {
    case 'D':
      if ((char)payload[1] == '1'){
        digitalWrite(4, HIGH);
        Serial.print("Deko an");
      }
      else {
        digitalWrite(4, LOW);
        Serial.print("Deko aus");
      }
      break;
    
    case 'L':
      if ((char)payload[1] == '1'){
        digitalWrite(0, HIGH);
        Serial.print("Lampion an");
      }
      else {
        digitalWrite(0, LOW);
        Serial.print("Lampion aus");
      }
      break;
    
    case 'V':
      if ((char)payload[1] == '1'){
        digitalWrite(14, HIGH);
        Serial.print("Vase an");
      }
      else {
        digitalWrite(14, LOW);
        Serial.print("Vase aus");
      }
      break;

    case 'A':
      if ((char)payload[1] == '1'){
        digitalWrite(0, HIGH);
        digitalWrite(4, HIGH);
        digitalWrite(14, HIGH);
        Serial.print("Alles an");
      }
      else {
        digitalWrite(0, LOW);
        digitalWrite(4, LOW);
        digitalWrite(14, LOW);
        Serial.print("Alles aus");
      }
      break;
      
    default:
      Serial.print("Message arrived [");
      Serial.print(topic);
      Serial.print("] ");
      for (int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
      }
      Serial.println();
      break;
  }
  Serial.println();
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ArduinoDeko", mqtt_user, mqtt_password)) {
      Serial.println("connected");
      client.publish("connectState", "connected");
      client.subscribe("switchCommand");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
