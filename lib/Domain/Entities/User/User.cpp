#include "User.hpp"

User::User(int32_t idUser, const std::string &rfidCard, const std::string &activationDate,
           const std::string &disableDate, int64_t maxElectricImpulseNumber, int64_t maxWaterImpulseNumber)
    : _idUser(idUser), _rfidCard(rfidCard), _authenticated(false), _activationDate(activationDate),
      _disableDate(disableDate), _maxElectricImpulseNumber(maxElectricImpulseNumber), _maxWaterImpulseNumber(maxWaterImpulseNumber)
{
}

User::User()
    : _idUser(0), _rfidCard(""), _authenticated(false), _activationDate(""), _disableDate(""),
      _maxElectricImpulseNumber(0), _maxWaterImpulseNumber(0)
{
}

int32_t User::getIdUser() const
{
  return _idUser;
}

void User::setIdUser(int32_t idUser)
{
  _idUser = idUser;
}

std::string User::getRfidCard() const
{
  return _rfidCard;
}

void User::setRfidCard(const std::string &rfidCard)
{
  _rfidCard = rfidCard;
}

std::string User::getActivationDate() const
{
  return _activationDate;
}

void User::setActivationDate(const std::string &activationDate)
{
  _activationDate = activationDate;
}

std::string User::getDisableDate() const
{
  return _disableDate;
}

void User::setDisableDate(const std::string &disableDate)
{
  _disableDate = disableDate;
}

int64_t User::getMaxElectricImpulseNumber() const
{
  return _maxElectricImpulseNumber;
}

void User::setMaxElectricImpulseNumber(int64_t maxElectricImpulseNumber)
{
  _maxElectricImpulseNumber = maxElectricImpulseNumber;
}

int64_t User::getMaxWaterImpulseNumber() const
{
  return _maxWaterImpulseNumber;
}

void User::setMaxWaterImpulseNumber(int64_t maxWaterImpulseNumber)
{
  _maxWaterImpulseNumber = maxWaterImpulseNumber;
}

bool User::isAuthenticated() const
{
  return _authenticated;
}

void User::setAuthenticated(bool authenticated)
{
  _authenticated = authenticated;
}
