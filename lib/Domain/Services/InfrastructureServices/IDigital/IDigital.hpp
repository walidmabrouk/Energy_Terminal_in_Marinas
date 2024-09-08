#ifndef IDIGITAL_HPP
#define IDIGITAL_HPP

class IDigital
{
public:
  virtual void digitalWrite(unsigned char address, unsigned char value) = 0;
  virtual unsigned char digitalRead(unsigned char address) const = 0;
  virtual ~IDigital() {} // Virtual destructor
};

#endif // IDIGITAL_HPP
