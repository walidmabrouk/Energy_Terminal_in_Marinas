#ifndef AUTHENTICATION_HPP
#define AUTHENTICATION_HPP


#include "../../lib/Domain/Services/InfrastructureServices/IRfidCommunication/IRfidCommunication.hpp"
#include "../../lib/Domain/Services/BuisnessServices/IRead/IRead.hpp"
#include "../../lib/Domain/Services/BuisnessServices/IAuthentication/IAuthentication.hpp"
#include "../../lib/Domain/Entities/User/User.hpp"
#include <string>

class Authentication : public IAuthentication
{
public:
  Authentication(const std::string &databaseFile, IRead *dataReader, IRfidCommunication *rfidReader);
  ~Authentication();

  bool authenticate() override;
  void logout() override;
  bool isAuthenticated() const override;

private:
  bool isRFIDTagValid(const std::string &rfidTag) const;
  bool readRFIDTagFromFile(const std::string &rfidTag) const;
  std::string readRFIDTagFromRfidReader() const;
  bool isCardActivated(const std::string &rfidTag) const;

  bool authenticated;
  std::string databaseFile;
  IRead *dataReader;
  IRfidCommunication *rfidReader;
  User user;
};

#endif // AUTHENTICATION_HPP
