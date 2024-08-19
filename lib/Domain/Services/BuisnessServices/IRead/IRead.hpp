#ifndef IREAD_HPP
#define IREAD_HPP

#include <string>

class IRead
{
public:
  virtual ~IRead() = default;
  virtual std::string readData() const = 0; 
};

#endif 
