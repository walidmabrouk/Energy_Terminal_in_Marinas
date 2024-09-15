#include "RfidCommunication.hpp"
#include <Arduino.h>

RfidCommunication::RfidCommunication(IDigital &digital)
    : currentState(RfidState::IDLE), digital(digital), flagCP(false), frameIndex(25), TrameIsOK(false)
{
  memset(tab, 0, sizeof(tab));
  Serial.println("RfidCommunication initialized");
}

RfidCommunication::~RfidCommunication()
{
  Serial.println("RfidCommunication destroyed");
}

void RfidCommunication::update()
{
  Serial.print("Current state: ");
  Serial.println(static_cast<int>(currentState)); // Debug state value

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
  case RfidState::CODE_RECEIVED:
    readRFID();
    break;
  }
}

void RfidCommunication::handleIdle()
{
  Serial.println("Handling IDLE state");
  if (isCardDetected())
  {
    Serial.println("Card detected");
    reset();
    //delay250ms();
    currentState = RfidState::CARD_DETECTED;
  }
}

void RfidCommunication::handleCardDetected()
{
  Serial.println("Handling CARD_DETECTED state");
  if (isStateZero())
  {
    Serial.println("State Zero detected");
    tab[frameIndex] = 0;
    flagD0 = false;
    frameIndex--;
    delay800us();
    currentState = RfidState::STATE_ZERO;
  }
  else if (isStateOne())
  {
    Serial.println("State One detected");
    tab[frameIndex] = 1;
    flagD1 = false;
    frameIndex--;
    delay800us();
    currentState = RfidState::STATE_ONE;
  }
}

void RfidCommunication::handleStateZero()
{
  Serial.print("Handling STATE_ZERO, frameIndex: ");
  Serial.println(frameIndex);
  currentState = (frameIndex <= 0) ? RfidState::RECEPTION_COMPLETE : RfidState::CARD_DETECTED;
}

void RfidCommunication::handleStateOne()
{
  Serial.print("Handling STATE_ONE, frameIndex: ");
  Serial.println(frameIndex);
  currentState = (frameIndex <= 0) ? RfidState::RECEPTION_COMPLETE : RfidState::CARD_DETECTED;
}

void RfidCommunication::handleReceptionComplete()
{
  Serial.println("Reception complete: 26 bits received");
  currentState = RfidState::FRAME_VERIFIED;
}

bool RfidCommunication::handleFrameVerified()
{
  Serial.println("Verifying frame");

  const int MSB_START = 13;
  const int MSB_END = 24;
  const int LSB_START = 1;
  const int LSB_END = 12;

  bool isMsbEvenParity = checkEvenParity(MSB_START, MSB_END);
  bool isLsbOddParity = checkOddParity(LSB_START, LSB_END);

  if (isMsbEvenParity && isLsbOddParity)
  {
    Serial.println("Frame verified successfully");
    TrameIsOK = true;
    currentState = RfidState::CODE_RECEIVED;
  }
  else
  {
    Serial.println("Frame verification failed");
    TrameIsOK = false;
    currentState = RfidState::IDLE;
  }
  return TrameIsOK;
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
  Serial.print("Even parity check, bit count: ");
  Serial.println(bitCount);
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
  Serial.print("Odd parity check, bit count: ");
  Serial.println(bitCount);
  return (bitCount % 2 != 0);
}

bool RfidCommunication::isCardDetected()
{
  while(1)
  {
    flagCP = digital.digitalRead(BSP::RFID_PIN_CP);
    if (flagCP == LOW)
    {
      break;
    }
  }
  Serial.print("Card detected (CP): ");
  Serial.println(!flagCP);
  return !flagCP;
}

bool RfidCommunication::isStateZero()
{
  bool state = digital.digitalRead(BSP::RFID_PIN_DATA_0);
  Serial.print("State Zero (D0): ");
  Serial.println(!state);
  return !state;
}

bool RfidCommunication::isStateOne()
{
  bool state = digital.digitalRead(BSP::RFID_PIN_DATA_1);
  Serial.print("State One (D1): ");
  Serial.println(!state);
  return !state;
}

void RfidCommunication::delay250ms()
{
  Serial.println("Delaying for 250ms");
  delay(250);
}

void RfidCommunication::delay800us()
{
  Serial.println("Delaying for 800us");
  delayMicroseconds(800);
}

void RfidCommunication::reset()
{
  Serial.println("Resetting RFID communication");
  frameIndex = 25;
  memset(tab, 0, sizeof(tab));
}

std::string RfidCommunication::readRFID() const
{
  std::string rfidTag;
  for (int i = 1; i <= 24; ++i)
  {
    rfidTag += std::to_string(tab[i]);
  }
  Serial.print("RFID Tag read: ");
  Serial.println(rfidTag.c_str());
  return rfidTag;
}
