#include <Arduino.h>
#include "BSP.hpp"
#include "../lib/Infrastructure/RfidCommunication/RfidCommunication.hpp"
#include "../lib/Infrastructure/RfidCommunication/RfidCommunication.cpp"
#include "../lib/Infrastructure/Digital/Digital.hpp"
#include "../lib/Infrastructure/Digital/Digital.cpp"
#include "../lib/Domain/Services/InfrastructureServices/IRfidCommunication/IRfidCommunication.hpp"
#include "../lib/Domain/Services/InfrastructureServices/IDigital/IDigital.hpp"

// Instantiate objects
Digital digital;
RfidCommunication rfidReader(digital);

void InitSystem()
{
  Serial.begin(115200);
  initBSP();
}

void InitApplication()
{
  // Application-specific initialization if needed
}

void TestAuthentication()
{
  rfidReader.update();
}

void setup()
{
  InitSystem();
  InitApplication();
}

void loop()
{
  TestAuthentication();
  delay(50000);
}
