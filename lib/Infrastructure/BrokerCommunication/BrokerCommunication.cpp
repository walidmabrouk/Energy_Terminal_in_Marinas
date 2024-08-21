#include "BrokerCommunication.hpp"
#include <iostream> 

// Send a command with a string payload
void BrokerCommunication::sendCommand(const std::string &topic, const std::string &payload)
{
  std::cout << "Sending command to topic '" << topic << "': " << payload << std::endl;
}

// Send a command with a binary payload
void BrokerCommunication::sendCommand(const std::string &topic, const uint8_t *payload, uint16_t size)
{
  std::cout << "Sending binary command to topic '" << topic << "' with size " << size << std::endl;
  // Actual implementation would send the binary payload to the MQTT broker
}

// Subscribe to a topic with a callback function
void BrokerCommunication::subscribe(const std::function<void(char *, uint8_t *, uint8_t)> &callback)
{
  std::cout << "Subscribed to topic with callback." << std::endl;
  // Mock message for demonstration purposes
  char topic[] = "test_topic";
  uint8_t payload[] = "test_message";
  // Call the callback with the mock message
  callback(topic, payload, sizeof(payload) - 1);
}
