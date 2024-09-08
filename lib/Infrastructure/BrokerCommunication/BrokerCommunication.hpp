#ifndef BROKERCOMMUNICATION_HPP
#define BROKERCOMMUNICATION_HPP

#include "../Domain/Services/InfrastructureServices/IBrokerCommunication/IBrokerCommunication.hpp"
#include "../Infrastructure/PubSubClient/src/PubSubClient.h"
#include <functional>
#include <cstdint>
#include <string>

class BrokerCommunication : public IBrokerCommunication
{
public:
  BrokerCommunication(PubSubClient &client);
  ~BrokerCommunication() override;

  void sendCommand(const std::string &topic, const std::string &payload) override;
  void sendCommand(const std::string &topic, const uint8_t *payload, uint16_t size) override;
  void subscribe(const std::function<void(char *, uint8_t *, uint8_t)> &callback) override;

private:
  PubSubClient &client;
};

#endif // BROKERCOMMUNICATION_HPP
