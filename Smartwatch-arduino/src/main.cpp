#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Need Mosquitto server on 1883 <- as a ubuntu-snap. restart system after install
// need my server on 1884


const char *mqttServer = "192.168.0.103";
const int mqttPort = 1884;
const char *mqttUser = "";
const char *mqttPassword = "";

const char *ssid = "ECUA";
const char *password = "godofwar";

int count = 0;

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char *topic, byte *payload, unsigned int length)
{

  Serial.print("Message arrived in topic: ");
  Serial.println(topic);

  Serial.print("Message:");
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }

  Serial.println();
  Serial.println("-----------------------");
}

void setup()
{
  Serial.begin(9600);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");

  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

  while (!client.connected())
  {
    Serial.println("Connecting to MQTT...");

    if (client.connect("ESP8266Client", mqttUser, mqttPassword))
    {

      Serial.println("connected");
    }
    else
    {

      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }

  client.subscribe("esp/test");


}

void loop()
{
  count += 1;
  client.loop();

  char buf[100];
  String s = "count : =  ";
  s.toCharArray(buf, s.length());
  String m1 = String(count);

  // for(int h = 0; h < m1.length(); h++)  {
  //   buf[h+  s.length() ]
  // }
  m1.toCharArray(buf +  s.length() - 1 , 100 - s.length()+1);



  client.publish("esp/test", buf );
  delay(3000);
  while (!client.connected())
  {
    Serial.println("Connecting to MQTT...");

    if (client.connect("ESP8266Client", mqttUser, mqttPassword))
    {

      Serial.println("connected");
      client.subscribe("esp/test");
    }
    else
    {

      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
}