#ifndef TERMINALCONFIGURATION_HPP
#define TERMINALCONFIGURATION_HPP

#include <string>

class TerminalConfiguration
{
private:
  std::string _wifiSSID;
  std::string _wifiPassword;

public:
  TerminalConfiguration(const std::string &wifiSSID, const std::string &wifiPassword);

  std::string getWifiSSID() const;
  void setWifiSSID(const std::string &newWifiSSID);

  std::string getPassword() const;
  void setPassword(const std::string &newPassword);

  void loadFromFile(const std::string &filename);
  void saveToFile(const std::string &filename) const;
};

#endif // TERMINALCONFIGURATION_HPP
