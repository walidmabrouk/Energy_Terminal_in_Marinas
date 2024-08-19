#ifndef IRFID_COMMUNICATION_HPP
#define IRFID_COMMUNICATION_HPP

#include <string>

class IRfidCommunication
{
public:
  virtual ~IRfidCommunication() {}

  virtual void update() = 0;
  virtual void reset() = 0;

  virtual bool isCardDetected() const = 0;
  virtual bool isStateZero() const = 0;
  virtual bool isStateOne() const = 0;
  virtual bool isFrameVerified() const = 0;
  virtual std::string readRFID() const = 0;
};

#endif 
