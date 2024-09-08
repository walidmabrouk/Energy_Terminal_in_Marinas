#include "BrokerCommunication.hpp"

BrokerCommunication::BrokerCommunication(PubSubClient &client) : client(client) {}

BrokerCommunication::~BrokerCommunication() = default;

void BrokerCommunication::sendCommand(const std::string &topic, const std::string &payload)
{
  client.publish(topic.c_str(), payload.c_str());
}

void BrokerCommunication::sendCommand(const std::string &topic, const uint8_t *payload, uint16_t size)
{
  client.publish(topic.c_str(), payload, size);
}

void BrokerCommunication::subscribe(const std::function<void(char *, uint8_t *, uint8_t)> &callback)
{
  client.setCallback([callback](char *topic, uint8_t *payload, unsigned int length)
                     { callback(topic, payload, length); });
}
