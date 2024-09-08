#include <Arduino.h>
#include <LittleFS.h>
#include "../Domain/Services/InfrastructureServices/IRfidCommunication/IRfidCommunication.hpp"
#include "../lib/Infrastructure/RfidCommunication/RfidCommunication.hpp"
#include "../lib/Infrastructure/RfidCommunication/RfidCommunication.cpp"
#include "BSP.hpp"

// Create an instance of IRfidCommunication
IRfidCommunication *rfidReader = new RfidCommunication();

void InitSystem()
{
  Serial.begin(115200);
  if (!LittleFS.begin())
  {
    Serial.println("Failed to mount LittleFS");
    while (1)
      ;
  }

  initBSP();
}

void InitApplication()
{
}

void TestAuthentication()
{
  // Continuously run the authentication loop
  rfidReader->update();
  if (rfidReader->isFrameVerified())
  {
    Serial.println("Authentication successful");
  }
  else
  {
    Serial.println("Authentication failed");
  }
}

void setup()
{
  InitSystem();
  InitApplication();
}

void loop()
{
  TestAuthentication();
}
