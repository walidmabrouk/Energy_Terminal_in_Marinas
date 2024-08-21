#include "CommandManager.hpp"

CommandManager::CommandManager(IBrokerCommunication &brokerComm,
                               IEnergySourceManager &energyMgr,
                               ISave &saveMgr)
    : brokerCommunication(brokerComm),
      energySourceManager(energyMgr),
      saveManager(saveMgr) {}

void CommandManager::executeCommand(const std::string &command)
{
  if (command == "setConfig")
  {
    // Implement setConfig logic
  }
  else if (command == "ActivateTerminal")
  {
    energySourceManager.activateTerminal();
  }
  else if (command == "DeactivateTerminal")
  {
    energySourceManager.disableTerminal();
  }
  else if (command == "ActivateElectricity")
  {
    energySourceManager.activateElectricity();
  }
  else if (command == "DeactivateElectricity")
  {
    energySourceManager.disableElectricity();
  }
  else if (command == "ActivateWater")
  {
    energySourceManager.activateWater();
  }
  else if (command == "DeactivateWater")
  {
    energySourceManager.disableWater();
  }
  else if (command == "ConfigureUser")
  {
    // Implement configureUser logic
  }
  else if (command == "ConfigureTariff")
  {
    // Implement configureTariff logic
  }
  else if (command == "GetElectricityConsumption")
  {
    // Implement getElectricityConsumption logic
    std::string consumptionData = "Electricity consumption data";
    brokerCommunication.sendCommand("currentElectricityConsumption", consumptionData);
  }
  else if (command == "GetWaterConsumption")
  {
    // Implement getWaterConsumption logic
    std::string consumptionData = "Water consumption data";
    brokerCommunication.sendCommand("currentWaterConsumption", consumptionData);
  }
}