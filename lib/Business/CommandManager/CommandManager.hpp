#ifndef COMMANDMANAGER_HPP
#define COMMANDMANAGER_HPP

#include "../Domain/Services/InfrastructureServices/IBrokerCommunication/IBrokerCommunication.hpp"
#include "../Domain/Services/BuisnessServices/IEnergySourceManager/IEnergySourceManager.hpp"
#include "../Domain/Services/BuisnessServices/ISave/ISave.hpp"

class CommandManager
{
public:
  // Constructor with dependencies injected
  CommandManager(IBrokerCommunication &brokerCommunication,
                 IEnergySourceManager &energyManager,
                 ISave &dataSaver);

  // Destructor
  ~CommandManager() = default;

  // Communication methods
  void sendCommand(const std::string &topic, const std::string &payload);
  void sendCommand(const std::string &topic, const uint8_t *payload, uint16_t size);
  void subscribe(const std::function<void(char *, uint8_t *, uint8_t)> &callback);

  // Energy management methods
  void activateTerminal();
  void disableTerminal();
  void activateElectricity();
  void disableElectricity();
  void activateWater();
  void disableWater();

  // Data saving methods
  void setConfig();
  void configureUser();
  void configureTariff();
  void getElectricityConsumption();
  void getWaterConsumption();

private:
  IBrokerCommunication &brokerCommunication;
  IEnergySourceManager &energyManager;
  ISave &dataSaver;

  void executeCommand(int commandId);
};

#endif // COMMANDMANAGER_HPP