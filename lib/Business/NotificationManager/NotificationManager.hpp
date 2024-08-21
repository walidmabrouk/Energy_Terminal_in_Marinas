#ifndef NOTIFICATIONMANAGER_HPP
#define NOTIFICATIONMANAGER_HPP

#include "../../Domain/Services/InfrastructureServices/IBrokerCommunication/IBrokerCommunication.hpp"
#include <string>
#include <cstdint>

class NotificationManager
{
private:
  IBrokerCommunication &brokerCommunication;


  // Utility methods to send notifications
  void sendElectricityConsumptionNotification(const std::string &data);
  void sendWaterConsumptionNotification(const std::string &data);
  void sendElectricityThresholdReachedNotification();
  void sendWaterThresholdReachedNotification();
  void sendElectricityConsumptionEndNotification();
  void sendWaterConsumptionEndNotification();

public:
  explicit NotificationManager(IBrokerCommunication &brokerComm);

  void notify(const std::string &message);

  // Methods to simulate different events
  void onElectricityConsumptionRequest();
  void onWaterConsumptionRequest();
  void onElectricityThresholdReached();
  void onWaterThresholdReached();
  void onElectricityConsumptionEnd();
  void onWaterConsumptionEnd();
};

#endif // NOTIFICATIONMANAGER_HPP
