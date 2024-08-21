#include "NotificationManager.hpp"

NotificationManager::NotificationManager(IBrokerCommunication &brokerComm)
    : brokerCommunication(brokerComm) {}

void NotificationManager::notify(const std::string &message)
{
  // Currently only sends a notification message
  std::string topic = "notification_topic";
  brokerCommunication.sendCommand(topic, message);
}

void NotificationManager::sendElectricityConsumptionNotification(const std::string &data)
{
  std::string topic = "currentElectricityConsumption";
  brokerCommunication.sendCommand(topic, data);
}

void NotificationManager::sendWaterConsumptionNotification(const std::string &data)
{
  std::string topic = "currentWaterConsumption";
  brokerCommunication.sendCommand(topic, data); // on listening
}

void NotificationManager::sendElectricityThresholdReachedNotification()
{
  std::string topic = "electricityThresholdReached";
  std::string message = "Electricity consumption has reached the threshold.";
  brokerCommunication.sendCommand(topic, message);
}

void NotificationManager::sendWaterThresholdReachedNotification()
{
  std::string topic = "waterThresholdReached";
  std::string message = "Water consumption has reached the threshold.";
  brokerCommunication.sendCommand(topic, message);
}

void NotificationManager::sendElectricityConsumptionEndNotification()
{
  std::string topic = "electricityConsumptionEnd";
  std::string message = "Electricity consumption has ended.";
  brokerCommunication.sendCommand(topic, message);
}

void NotificationManager::sendWaterConsumptionEndNotification()
{
  std::string topic = "waterConsumptionEnd";
  std::string message = "Water consumption has ended.";
  brokerCommunication.sendCommand(topic, message);
}

void NotificationManager::onElectricityConsumptionRequest()
{
  // Simulate receiving a request for electricity consumption data
  std::string data = "Electricity consumption data";
  sendElectricityConsumptionNotification(data);
}

void NotificationManager::onWaterConsumptionRequest()
{
  // Simulate receiving a request for water consumption data
  std::string data = "Water consumption data";
  sendWaterConsumptionNotification(data);
}

void NotificationManager::onElectricityThresholdReached()
{
  // Simulate reaching the electricity consumption threshold
  sendElectricityThresholdReachedNotification();
}

void NotificationManager::onWaterThresholdReached()
{
  // Simulate reaching the water consumption threshold
  sendWaterThresholdReachedNotification();
}

void NotificationManager::onElectricityConsumptionEnd()
{
  // Simulate the end of electricity consumption
  sendElectricityConsumptionEndNotification();
}

void NotificationManager::onWaterConsumptionEnd()
{
  // Simulate the end of water consumption
  sendWaterConsumptionEndNotification();
}


