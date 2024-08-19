#ifndef IAUTHENTICATION_HPP
#define IAUTHENTICATION_HPP

#include <string>

class IAuthentication
{
public:
  virtual ~IAuthentication() = default;

  virtual bool authenticate() = 0; 
  virtual void logout() = 0;
  virtual bool isAuthenticated() const = 0;
};

#endif // IAUTHENTICATION_HPP
