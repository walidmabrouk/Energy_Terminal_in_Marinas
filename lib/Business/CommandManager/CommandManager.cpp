#include "CommandManager.hpp"

// Constructor
CommandManager::CommandManager(IBrokerCommunication &brokerCommunication,
                               IEnergySourceManager &energyManager,
                               ISave &dataSaver)
    : brokerCommunication(brokerCommunication),
      energyManager(energyManager),
      dataSaver(dataSaver) {}

// Communication methods
void CommandManager::sendCommand(const std::string &topic, const std::string &payload)
{
  brokerCommunication.sendCommand(topic, payload);
}

void CommandManager::sendCommand(const std::string &topic, const uint8_t *payload, uint16_t size)
{
  brokerCommunication.sendCommand(topic, payload, size);
}

void CommandManager::subscribe(const std::function<void(char *, uint8_t *, uint8_t)> &callback)
{
  brokerCommunication.subscribe(callback);
}

// Energy management methods
void CommandManager::activateTerminal()
{
  energyManager.activateTerminal();
}

void CommandManager::disableTerminal()
{
  energyManager.disableTerminal();
}

void CommandManager::activateElectricity()
{
  energyManager.activateElectricity();
}

void CommandManager::disableElectricity()
{
  energyManager.disableElectricity();
}

void CommandManager::activateWater()
{
  energyManager.activateWater();
}

void CommandManager::disableWater()
{
  energyManager.disableWater();
}

// Data saving methods
void CommandManager::setConfig()
{
  dataSaver.setConfig();
}

void CommandManager::configureUser()
{
  dataSaver.configureUser();
}

void CommandManager::configureTariff()
{
  dataSaver.configureTariff();
}

void CommandManager::getElectricityConsumption()
{
  dataSaver.getElectricityConsumption();
}

void CommandManager::getWaterConsumption()
{
  dataSaver.getWaterConsumption();
}

// Execute command based on command ID
void CommandManager::executeCommand(int commandId)
{
  switch (commandId)
  {
  case 1:
    setConfig();
    break;
  case 2:
    activateTerminal();
    break;
  case 3:
    disableTerminal();
    break;
  case 4:
    activateElectricity();
    break;
  case 5:
    disableElectricity();
    break;
  case 6:
    activateWater();
    break;
  case 7:
    disableWater();
    break;
  case 8:
    configureUser();
    break;
  case 9:
    configureTariff();
    break;
  case 10:
    getElectricityConsumption();
    break;
  case 11:
    getWaterConsumption();
    break;
  default:
    // Handle unknown command
    break;
  }
}
