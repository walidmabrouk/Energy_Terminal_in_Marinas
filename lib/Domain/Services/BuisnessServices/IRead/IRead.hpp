#ifndef IREAD_HPP
#define IREAD_HPP

#include <string>

class IRead
{
public:
  virtual ~IRead() = default;
  virtual std::string getData(const std::string &key, const std::string &field) const = 0;
};

#endif // IREAD_HPP
