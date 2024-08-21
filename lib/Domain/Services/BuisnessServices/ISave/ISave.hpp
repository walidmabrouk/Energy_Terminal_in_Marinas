#ifndef ISAVE_HPP
#define ISAVE_HPP

#include <string>

class ISave
{
public:
  virtual ~ISave() = default;
  virtual void saveData(const std::string &data) = 0; 
  virtual void setConfig() = 0;
  virtual void configureUser() = 0;
  virtual void configureTariff() = 0;
  virtual void getElectricityConsumption() = 0;
  virtual void getWaterConsumption() = 0;
};

#endif 
