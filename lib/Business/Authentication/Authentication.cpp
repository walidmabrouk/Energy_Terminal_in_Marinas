#include "Authentication.hpp"
#include <LittleFS.h>

Authentication::Authentication(const std::string &databaseFile, IRead *dataReader, IRfidCommunication *rfidReader)
    : authenticated(false), databaseFile(databaseFile), dataReader(dataReader), rfidReader(rfidReader)
{
}

Authentication::~Authentication() = default;

bool Authentication::authenticate()
{
  std::string rfidTagFromReader = readRFIDTagFromRfidReader();
  if (isRFIDTagValid(rfidTagFromReader))
  {
    if (isCardActivated(rfidTagFromReader))
    {
      authenticated = true;
      return true;
    }
  }
  return false;
}

void Authentication::logout()
{
  authenticated = false;
}

bool Authentication::isAuthenticated() const
{
  return authenticated;
}

bool Authentication::isRFIDTagValid(const std::string &rfidTag) const
{
  return readRFIDTagFromFile(rfidTag);
}

bool Authentication::readRFIDTagFromFile(const std::string &rfidTag) const
{
  std::string tagData = dataReader->readData();
  return tagData == rfidTag;
}

std::string Authentication::readRFIDTagFromRfidReader() const
{
  return rfidReader->readRFID();
}

bool Authentication::isCardActivated(const std::string &rfidTag) const
{
  if (user.getDisableDate > dateSystem)
  {
    return false;
  }
  return true;
}
