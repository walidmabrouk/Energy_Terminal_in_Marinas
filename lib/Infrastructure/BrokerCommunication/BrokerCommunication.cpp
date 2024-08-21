#include "BrokerCommunication.hpp"

// Constructor
BrokerCommunication::BrokerCommunication(Client &client) : client(client) {}

// Destructor
BrokerCommunication::~BrokerCommunication() {}

// Send command with string payload
void BrokerCommunication::sendCommand(const std::string &topic, const std::string &payload)
{
  if (!client.publish(topic.c_str(), payload.c_str()))
  {
    // Handle publish error (optional)
  }
}

// Send command with byte array payload
void BrokerCommunication::sendCommand(const std::string &topic, const uint8_t *payload, uint16_t size)
{
  if (!client.publish(topic.c_str(), payload, size))
  {
    // Handle publish error (optional)
  }
}

// Subscribe to a topic with a callback function
void BrokerCommunication::subscribe(const std::function<void(char *, uint8_t *, uint8_t)> &callback)
{
  client.setCallback(callback);
}
