#ifndef DIGITAL_HPP
#define DIGITAL_HPP

#include "../Domain/Services/InfrastructureServices/IDigital/IDigital.hpp"
#include <Arduino.h>

class Digital : public IDigital
{
public:
  void digitalWrite(unsigned char address, unsigned char value) override;
  unsigned char digitalRead(unsigned char address) const override;
};

#endif // DIGITAL_HPP
