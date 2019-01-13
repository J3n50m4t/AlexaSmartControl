#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"
#include "userconfig.h"

WiFiClient espClient;
PubSubClient client(espClient);

#define DHTPIN 12
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);


long lastMsg = 0;
char msg[50];
int value = 0;
String temp_str;
char temp[50];

void setup() {
  // Initialize the BUILTIN_LED pin as an output while debugging
       
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void setup_wifi() {
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
int timeSinceLastRead = 0;
void loop() {
  
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  if(timeSinceLastRead > 2000) {
    float temperature = dht.readTemperature();
    if (isnan(temperature)) {
      timeSinceLastRead = 0;
      return;
    }
    temp_str = String(temperature);
    temp_str.toCharArray(temp, temp_str.length() + 1); //packaging up the data to publish to mqtt whoa...
    client.publish("tvboardtemp", temp);
    timeSinceLastRead = 0;
  }
  delay(100);
  timeSinceLastRead += 100;
  
}
