#include <ESP8266WiFi.h>
#include <MQTT.h>
#include <jwt.h>
#include <time.h>

#include "ciotc_config.h" // Configure with your settings

WiFiClient net;
MQTTClient client;


unsigned int priv_key[8];

String getJwt() {
  // Disable software watchdog as these operations can take a while.
  ESP.wdtDisable();
  String jwt = CreateJwt(project_id, time(nullptr), priv_key);
  ESP.wdtEnable(0);
  return jwt;
}

const char* host = "cloudiotdevice.googleapis.com";
const int httpsPort = 443;

String pwd;

// Fills the priv_key global variable with private key str which is of the form
// aa:bb:cc:dd:ee:...
void fill_priv_key(const char* priv_key_str) {
  priv_key[8] = 0;
  for (int i = 7; i >= 0; i--) {
    priv_key[i] = 0;
    for (int byte_num = 0; byte_num < 4; byte_num++) {
      priv_key[i] = (priv_key[i] << 8) + strtoul(priv_key_str, NULL, 16);
      priv_key_str += 3;
    }
  }
}




unsigned long lastMillis = 0;

void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnecting...");
//  while (!client.connect("arduino", "try", "try")) {
//    Serial.print(".");
//    delay(1000);
//  }
//
//  Serial.println("\nconnected!");
//
//  client.subscribe("/hello");
//  // client.unsubscribe("/hello");
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  // Note: Local domain names (e.g. "Computer.local" on OSX) are not supported by Arduino.
  // You need to set the IP address directly.
  client.begin("mqtt.googleapis.com", 8883, net);
//  client.onMessage(messageReceived);

//  const char* jwt = "{json web token}";
//  const char* device = "projects/{project-id}/locations/{cloud-region}/registries/{registry-id}/devices/{device-id}";
//  Serial.print("Connecting to mqtt");
//
//  while (!client.connect(device, "unused", jwt)) {
//    Serial.print(".");
//    delay(1000);
//  }

  connect();
}

void loop() {
//  client.loop();
//  delay(10);  // <- fixes some issues with WiFi stability
//
//  if (!client.connected()) {
//    connect();
//  }
//
//  // publish a message roughly every second.
//  if (millis() - lastMillis > 1000) {
//    lastMillis = millis();
//    client.publish("/hello", "world");
//  }
}
