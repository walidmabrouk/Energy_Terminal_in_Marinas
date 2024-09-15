#ifndef DIGITAL_HPP
#define DIGITAL_HPP

#include "../Domain/Services/InfrastructureServices/IDigital/IDigital.hpp"
#include <Arduino.h>

class Digital : public IDigital
{
public:
  void digitalWrite(uint8_t address, uint8_t value) override;
  uint8_t digitalRead(uint8_t address) const override;
};

#endif // DIGITAL_HPP
