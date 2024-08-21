#include "BSP.hpp"
#include <Arduino.h>
#include <WiFi.h>

const char *ssid = "cafe_saphir_5G";
const char *pass = "987654321";

void InitSystem();
void InitApplication();
void MyProgram();
void setupWifi();

void setupWifi()
{
  delay(100);
  Serial.print("\nConnecting to");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print("-");
  }
  Serial.print("\nConnected to");
  Serial.println(ssid);
}
void setup()
{
  InitSystem();
  InitApplication();
}

void InitSystem()
{
  Serial.begin(115200);
  setupWifi();
  if (!LittleFS.begin())
  {
    Serial.println("An Error has occurred while mounting LittleFS");
    while (true)
    {
    }
  }

  Serial.println("LittleFS mounted successfully");
  initBSP();
}

void InitApplication()
{
  digitalWrite(BSP::TERMINAL_PIN, LOW);
  digitalWrite(BSP::WATER_PIN, LOW);
  digitalWrite(BSP::ELECTRICITY_PIN, LOW);
}

void MyProgram()
{
  if (authenticate())
  {
    Serial.println("Authenticated successfully");
  }
  else
  {
    Serial.println("Authentication failed");
  }
  delay(1000);
}

void loop()
{
  MyProgram();
  delay(10);
}
