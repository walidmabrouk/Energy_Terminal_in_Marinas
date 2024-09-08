#include <Arduino.h>
#include <LittleFS.h>
#include "../Domain/Services/InfrastructureServices/IFile/IFile.hpp"
#include "../lib/Infrastructure/File/MyFile.hpp"
#include "../Domain/Services/InfrastructureServices/IRfidCommunication/IRfidCommunication.hpp"
#include "../lib/Infrastructure/RfidCommunication/RfidCommunication.hpp"
#include "../lib/Business/Authentication/Authentication.hpp"

// Create instances of IFile and IRfidCommunication implementations
IRead *fileHandler = new MyFile();                        // Ensure MyFile implements IFile
IRfidCommunication *rfidReader = new RfidCommunication(); // Ensure RfidCommunication implements IRfidCommunication

// Create an instance of Authentication with the required arguments
Authentication *authentication = new Authentication("path/to/database", fileHandler, rfidReader);

void InitSystem()
{
  Serial.begin(115200);
  if (!LittleFS.begin())
  {
    Serial.println("Failed to mount LittleFS");
    while (1)
      ; // Halt if LittleFS fails to initialize
  }
}

void InitApplication()
{
  // Initialization code for your application, if needed
}

void TestAuthentication()
{
  if (authentication->authenticate())
  {
    Serial.println("Authentication successful!");
  }
  else
  {
    Serial.println("Authentication failed.");
  }
}

void MyProgram()
{
  TestAuthentication();
  delay(1000);
}

void setup()
{
  InitSystem();
  InitApplication();
}

void loop()
{
  MyProgram();
  delay(10);
}

void cleanup()
{
  delete authentication;
  delete fileHandler;
  delete rfidReader;
}
