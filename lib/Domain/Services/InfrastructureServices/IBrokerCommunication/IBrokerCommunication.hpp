#ifndef IBROKERCOMMUNICATION_HPP
#define IBROKERCOMMUNICATION_HPP

#include <functional>
#include <cstdint>
#include <string>

class IBrokerCommunication
{
public:
  virtual ~IBrokerCommunication() = default;

  virtual void sendCommand(const std::string &topic, const std::string &payload) = 0;
  virtual void sendCommand(const std::string &topic, const uint8_t *payload, uint16_t size) = 0;
  virtual void subscribe(const std::function<void(char *, uint8_t *, uint8_t)> &callback) = 0;
};

#endif // IBROKERCOMMUNICATION_HPP
