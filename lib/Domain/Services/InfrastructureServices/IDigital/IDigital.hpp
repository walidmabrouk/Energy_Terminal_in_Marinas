#ifndef IDIGITAL_HPP
#define IDIGITAL_HPP

class IDigital
{
public:
  virtual ~IDigital() = default;

  virtual void writeDigitalPin(int pin, bool value) = 0;
  virtual bool readDigitalPin(int pin) const = 0;
};

#endif 
