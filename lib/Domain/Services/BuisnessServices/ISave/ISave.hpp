#ifndef ISAVE_HPP
#define ISAVE_HPP

#include <string>

class ISave
{
public:
  virtual ~ISave() = default;
  virtual void saveData(const std::string &data) = 0;
};

#endif 
