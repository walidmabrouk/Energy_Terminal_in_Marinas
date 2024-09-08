#ifndef AUTHENTICATION_HPP
#define AUTHENTICATION_HPP

#include "../lib/Domain/Services/BuisnessServices/IAuthentication/IAuthentication.hpp"
#include "../lib/Domain/Services/InfrastructureServices/IRfidCommunication/IRfidCommunication.hpp"
#include "../lib/Domain/Services/BuisnessServices/IRead/IRead.hpp"
#include "../lib/Domain/Services/BuisnessServices/ISave/ISave.hpp"
#include "../lib/Domain/Entities/User/User.hpp"
#include <string>
#include <ctime> 
#include <sys/time.h>

class Authentication : public IAuthentication
{
public:
  Authentication(IRead *dataReader, IRfidCommunication *rfidReader, ISave *save);
  ~Authentication();

  bool authenticate() override;
  void logout() override;
  bool isAuthenticated() const override;

private:
  bool isRFIDTagValid(const std::string &rfidTag) const;
  bool readRFIDTagFromFile(const std::string &rfidTag) const;
  bool isCardActivated(const std::string &rfidTag) const;
  std::string readRFIDTagFromRfidReader() const;
  std::string getCurrentTime() const;
  IRead *dataReader;
  IRfidCommunication *rfidReader;
  ISave *save;
  User user;
};

#endif // AUTHENTICATION_HPP
