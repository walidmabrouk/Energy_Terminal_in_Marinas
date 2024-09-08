#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <cstdint>

class User
{
private:
  int32_t _idUser;
  std::string _rfidCard;
  bool _authenticated;
  std::string _activationDate;
  std::string _disableDate;
  int64_t _maxElectricImpulseNumber;
  int64_t _maxWaterImpulseNumber;

public:
  User(int32_t idUser, const std::string &rfidCard, const std::string &activationDate,
       const std::string &disableDate, int64_t maxElectricImpulseNumber, int64_t maxWaterImpulseNumber);
  User();

  int32_t getIdUser() const;
  void setIdUser(int32_t idUser);

  std::string getRfidCard() const;
  void setRfidCard(const std::string &rfidCard);

  std::string getActivationDate() const;
  void setActivationDate(const std::string &activationDate);

  std::string getDisableDate() const;
  void setDisableDate(const std::string &disableDate);

  int64_t getMaxElectricImpulseNumber() const;
  void setMaxElectricImpulseNumber(int64_t maxElectricImpulseNumber);

  int64_t getMaxWaterImpulseNumber() const;
  void setMaxWaterImpulseNumber(int64_t maxWaterImpulseNumber);

  bool isAuthenticated() const;
  void setAuthenticated(bool authenticated);
};

#endif
