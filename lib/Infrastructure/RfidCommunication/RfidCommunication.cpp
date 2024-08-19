#include "RfidCommunication.hpp"
#include <iostream>

RfidCommunication::RfidCommunication()
    : currentState(RfidState::IDLE), flagD0(false), flagD1(false), flagCP(false), frameIndex(0)
{
  memset(tab, 0, sizeof(tab));
}

void RfidCommunication::update()
{
  switch (currentState)
  {
  case RfidState::IDLE:
    handleIdle();
    break;
  case RfidState::CARD_DETECTED:
    handleCardDetected();
    break;
  case RfidState::STATE_ZERO:
    handleStateZero();
    break;
  case RfidState::STATE_ONE:
    handleStateOne();
    break;
  case RfidState::RECEPTION_COMPLETE:
    handleReceptionComplete();
    break;
  case RfidState::FRAME_VERIFIED:
    handleFrameVerified();
    break;
  }
}

void RfidCommunication::reset()
{
  currentState = RfidState::IDLE;
  flagD0 = false;
  flagD1 = false;
  flagCP = false;
  frameIndex = 25;
  memset(tab, 0, sizeof(tab));
}

void RfidCommunication::handleIdle()
{
  if (isCardDetected())
  {
    reset();
    delay250ms();
    currentState = RfidState::CARD_DETECTED;
  }
}

void RfidCommunication::handleCardDetected()
{
  if (isStateZero() && flagD0)
  {
    currentState = RfidState::STATE_ZERO;
    tab[frameIndex] = 0;
    flagD0 = false;
    frameIndex--;
    delay800us();
  }
  else if (isStateOne() && flagD1)
  {
    currentState = RfidState::STATE_ONE;
    tab[frameIndex] = 1;
    flagD1 = false;
    frameIndex--;
    delay800us();
  }
}

void RfidCommunication::handleStateZero()
{
  if (frameIndex <= 0)
  {
    currentState = RfidState::RECEPTION_COMPLETE;
  }
  else
  {
    currentState = RfidState::CARD_DETECTED;
  }
}

void RfidCommunication::handleStateOne()
{
  if (frameIndex <= 0)
  {
    currentState = RfidState::RECEPTION_COMPLETE;
  }
  else
  {
    currentState = RfidState::CARD_DETECTED;
  }
}

void RfidCommunication::handleReceptionComplete()
{
  if (isFrameVerified())
  {
    currentState = RfidState::FRAME_VERIFIED;
  }
}

void RfidCommunication::handleFrameVerified()
{
  const int MSB_START = 13;
  const int MSB_END = 24;
  const int LSB_START = 1;
  const int LSB_END = 12;

  bool isMsbEvenParity = checkEvenParity(MSB_START, MSB_END);
  bool isLsbOddParity = checkOddParity(LSB_START, LSB_END);

  if (isMsbEvenParity && isLsbOddParity)
  {
    TrameIsOK = true;
    currentState = RfidState::CODE_RECEIVED;
  }
  else
  {
    TrameIsOK = false;
    currentState = RfidState::IDLE;
  }
}

bool RfidCommunication::checkEvenParity(int start, int end)
{
  int bitCount = 0;
  for (int i = start; i <= end; ++i)
  {
    if (tab[i] == 1)
    {
      ++bitCount;
    }
  }
  return (bitCount % 2 == 0);
}

bool RfidCommunication::checkOddParity(int start, int end)
{
  int bitCount = 0;
  for (int i = start; i <= end; ++i)
  {
    if (tab[i] == 1)
    {
      ++bitCount;
    }
  }
  return (bitCount % 2 != 0);
}

bool RfidCommunication::isCardDetected()
{
  return flagCP;
}

bool RfidCommunication::isStateZero()
{
  return flagD0;
}

bool RfidCommunication::isStateOne()
{
  return flagD1;
}

bool RfidCommunication::isFrameVerified()
{
  return TrameIsOK;
}

void RfidCommunication::delay250ms()
{
  delay(250);
}

void RfidCommunication::delay800us()
{
  delayMicroseconds(800);
}
std::string RfidCommunication::readRFID() const
{
  std::string rfidTag;
  for (int i = 1; i <= 24; ++i)
  {
    rfidTag += std::to_string(tab[i]);
  }

  return rfidTag;
}
