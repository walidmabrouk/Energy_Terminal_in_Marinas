#ifndef IRFIDCOMMUNICATION_HPP
#define IRFIDCOMMUNICATION_HPP

#include <string>

class IRfidCommunication
{
public:
  virtual ~IRfidCommunication() = default;
  virtual void update() = 0;
  virtual void reset() = 0;
  virtual bool isCardDetected() = 0;
  virtual bool isStateZero() = 0;
  virtual bool isStateOne() = 0;
  virtual bool isFrameVerified() = 0;
  virtual std::string readRFID() const = 0;
};

#endif // IRFIDCOMMUNICATION_HPP
