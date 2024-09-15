#ifndef IDIGITAL_HPP
#define IDIGITAL_HPP

#include <cstdint> 

class IDigital
{
public:
  virtual void digitalWrite(uint8_t address, uint8_t value) = 0;
  virtual uint8_t digitalRead(uint8_t address) const = 0;
  virtual ~IDigital() = default; // Virtual destructor
};

#endif // IDIGITAL_HPP
