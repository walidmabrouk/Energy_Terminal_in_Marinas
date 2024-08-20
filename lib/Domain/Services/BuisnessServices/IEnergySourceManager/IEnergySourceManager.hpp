#ifndef IENERGYSOURCEMANAGER_HPP
#define IENERGYSOURCEMANAGER_HPP

class IEnergySourceManager
{
public:
  virtual ~IEnergySourceManager() = default;

  virtual void activateTerminal() = 0;
  virtual void disableTerminal() = 0;
  virtual void activateWater() = 0;
  virtual void disableWater() = 0;
  virtual void activateElectricity() = 0;
  virtual void disableElectricity() = 0;
};

#endif 
