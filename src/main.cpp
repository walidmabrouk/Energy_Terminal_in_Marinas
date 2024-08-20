#include "bsp.h"
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
    return;
  }
  Serial.println("LittleFS mounted successfully");
  initBSP();
}

void InitApplication()
{

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
