#ifndef ENERGYSOURCEMANAGER_HPP
#define ENERGYSOURCEMANAGER_HPP

#include "../Domain/Services/BuisnessServices/IEnergySourceManager/IEnergySourceManager.hpp"
#include "../Domain/Services/InfrastructureServices/IDigital/IDigital.hpp"
#include "../../include/BSP.hpp"
class EnergySourceManager : public IEnergySourceManager
{
public:
  EnergySourceManager(IDigital &digitalInterface);
  ~EnergySourceManager() override = default;

  void activateTerminal() override;
  void disableTerminal() override;
  void activateWater() override;
  void disableWater() override;
  void activateElectricity() override;
  void disableElectricity() override;

private:
  IDigital &m_digitalInterface;

  void setPinState(int pin, bool state);
};

#endif // ENERGYSOURCEMANAGER_HPP
