#ifndef ISAVE_HPP
#define ISAVE_HPP

#include <string>

class ISave
{
public:
  virtual ~ISave() = default;
  virtual void persistData(const std::string &key, const std::string &field, bool value) = 0;
};

#endif // ISAVE_HPP
