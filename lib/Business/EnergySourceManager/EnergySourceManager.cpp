#include "EnergySourceManager.hpp"

EnergySourceManager::EnergySourceManager(IDigital &digitalInterface)
    : m_digitalInterface(digitalInterface) {}

void EnergySourceManager::activateTerminal()
{
  setPinState(BSP::TERMINAL_PIN, true);
}

void EnergySourceManager::disableTerminal()
{
  setPinState(BSP::TERMINAL_PIN, false);
}

void EnergySourceManager::activateWater()
{
  setPinState(BSP::WATER_PIN, true);
}

void EnergySourceManager::disableWater()
{
  setPinState(BSP::WATER_PIN, false);
}

void EnergySourceManager::activateElectricity()
{
  setPinState(BSP::ELECTRICITY_PIN, true);
}

void EnergySourceManager::disableElectricity()
{
  setPinState(BSP::ELECTRICITY_PIN, false);
}

void EnergySourceManager::setPinState(int pin, bool state)
{
  m_digitalInterface.writeDigitalPin(pin, state);
}
