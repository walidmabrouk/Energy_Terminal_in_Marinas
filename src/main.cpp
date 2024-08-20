#include "BSP.hpp"
#include <Arduino.h>

void InitSystem();
void InitApplication();
void MyProgram();

void setup()
{
  InitSystem();
  InitApplication();
}

void InitSystem()
{
  Serial.begin(115200);

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
