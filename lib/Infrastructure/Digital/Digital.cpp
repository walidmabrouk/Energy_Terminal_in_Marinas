#include "Digital.hpp"

void Digital::digitalWrite(unsigned char address, unsigned char value)
{
  ::digitalWrite(address, value);
}

unsigned char Digital::digitalRead(unsigned char address) const
{
  return ::digitalRead(address); 
}
