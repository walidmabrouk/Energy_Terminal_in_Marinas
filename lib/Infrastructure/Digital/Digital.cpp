#include "Digital.hpp"

void Digital::digitalWrite(uint8_t address, uint8_t value)
{
  ::digitalWrite(address, value);
}

uint8_t Digital::digitalRead(uint8_t address) const
{
  return ::digitalRead(address);
}
