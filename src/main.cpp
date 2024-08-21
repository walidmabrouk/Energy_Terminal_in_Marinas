#include "BSP.hpp"
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

const char *wifi_ssid = "H267A_C0BE_2.4G";
const char *wifi_pass = "xQ9Zks6N";
const char *mqtt_server = "192.168.100.61";
const char *inTopic = "home/livingroom/temperature"; // Define your input topic
const char *outTopic = "home/livingroom/response";   // Define your output topic

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Received message on topic: ");
  Serial.println(topic);
  Serial.print("Message: ");
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void reconnect()
{
  while (!client.connected())
  {
    Serial.print("\nConnecting to ");
    Serial.println(mqtt_server);
    if (client.connect("koikoikoi"))
    {
      Serial.print("\nConnected to ");
      Serial.println(mqtt_server);
      client.subscribe(inTopic); // Subscribe to the input topic
    }
    else
    {
      Serial.print("\nFailed to connect, trying again in 5 seconds");
      delay(5000);
    }
  }
}

void setupWifi()
{
  delay(100);
  Serial.print("\nConnecting to ");
  Serial.println(wifi_ssid);
  WiFi.begin(wifi_ssid, wifi_pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print("-");
  }
  Serial.print("\nConnected to ");
  Serial.println(wifi_ssid);
}

void InitSystem()
{
  Serial.begin(115200);
  setupWifi();
  if (!LittleFS.begin())
  {
    Serial.println("An Error has occurred while mounting LittleFS");
  }

  Serial.println("LittleFS mounted successfully");
  initBSP();

  // Set MQTT broker
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void InitApplication()
{
  digitalWrite(BSP::TERMINAL_PIN, LOW);
  digitalWrite(BSP::WATER_PIN, LOW);
  digitalWrite(BSP::ELECTRICITY_PIN, LOW);
}

void MyProgram()
{
  if (!client.connected())
  {
    reconnect();
  }
  client.loop();

  // if (authenticate())
  // {
  //     Serial.println("Authenticated successfully");
  // }
  // else
  // {
  //     Serial.println("Authentication failed");
  // }
  delay(1000);
}

void setup()
{
  InitSystem();
  InitApplication();
}

void loop()
{
  // unsigned long currentTime = millis();
  // static unsigned long lastTime = 0;
  // static int count = 0;
  // char messages[75];

  // if (currentTime - lastTime > 2000)
  // {
  //   count++;
  //   snprintf(messages, 75, "%d", count);
  //   Serial.print("Sending message: ");
  //   Serial.println(messages);
  //   client.publish(outTopic, messages);
  //   lastTime = millis();
  // }
  MyProgram();
  delay(10);
}
