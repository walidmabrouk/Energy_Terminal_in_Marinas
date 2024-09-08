#include "Authentication.hpp"

Authentication::Authentication(IRead *dataReader, IRfidCommunication *rfidReader, ISave *save)
    : dataReader(dataReader), rfidReader(rfidReader), save(save)
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
            save->persistData(rfidTagFromReader, "authenticated", true);
            return true;
        }
    }
    save->persistData(rfidTagFromReader, "authenticated", false);
    return false;
}

void Authentication::logout()
{
    std::string rfidTagFromReader = readRFIDTagFromRfidReader();
    save->persistData(rfidTagFromReader, "authenticated", false);
}

bool Authentication::isAuthenticated() const
{
    std::string rfidTagFromReader = readRFIDTagFromRfidReader();
    return dataReader->getData(rfidTagFromReader, "authenticated") == "true";
}

bool Authentication::isRFIDTagValid(const std::string &rfidTagFromRfidReader) const
{
  return readRFIDTagFromFile(rfidTagFromRfidReader);
}

bool Authentication::readRFIDTagFromFile(const std::string &rfidTagFromRfidReader) const
{
  std::string rfidTagFromFile = dataReader->getData(rfidTagFromRfidReader, "_rfidTag");
  ;
  return rfidTagFromFile == rfidTagFromRfidReader;
}

std::string Authentication::readRFIDTagFromRfidReader() const
{
    return rfidReader->readRFID();
}

bool Authentication::isCardActivated(const std::string &rfidTag) const
{
 
  std::string activationDateOFRfidTag = dataReader->getData(rfidTag, "_activationDate");
  std::string disableDateOFRfidTag = dataReader->getData(rfidTag, "_disableDate");
  std::string currentTime = getCurrentTime();  

  return (activationDateOFRfidTag <= currentTime) && (currentTime <= disableDateOFRfidTag);
}

std::string Authentication::getCurrentTime() const
{
  struct timeval tv;
  gettimeofday(&tv, nullptr);

  time_t now = tv.tv_sec;
  struct tm *timeinfo = localtime(&now);

  char buffer[20];
  strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
  return std::string(buffer);
}