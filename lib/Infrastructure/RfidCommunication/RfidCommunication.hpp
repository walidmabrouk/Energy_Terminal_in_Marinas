#ifndef RFID_COMMUNICATION_HPP
#define RFID_COMMUNICATION_HPP

#include <Arduino.h>
#include "BSP.hpp"

class RfidState;

class RfidCommunication
{
public:
  enum class Event
  {
    BIT_RECEIVED,
    TIMEOUT,
    CARD_DETECTED,
    INVALID_PARITY
  };

  enum class StateId
  {
    IDLE,
    RECEIVING,
    PROCESSING
  };

  static const uint8_t WIEGAND_BIT_COUNT = 34;
  static const uint32_t TIMEOUT_MS = 20;

  RfidCommunication(BSP &bsp, uint8_t data0Pin, uint8_t data1Pin, uint8_t cpPin);
  void begin();
  void handleEvent(Event event);
  bool isCardDetected() const;
  uint32_t getCardId() const;
  bool isValid() const;

private:
  static RfidCommunication *_instance;
  static void IRAM_ATTR data0Interrupt();
  static void IRAM_ATTR data1Interrupt();
  static void IRAM_ATTR cpInterrupt();

  void addBit(bool bit);
  bool validateParity();
  void changeState(RfidState *newState, StateId newStateId);

  BSP &_bsp;
  uint8_t _data0Pin;
  uint8_t _data1Pin;
  uint8_t _cpPin;

  RfidState *_currentState;
  StateId _currentStateId;
  uint64_t _cardData;
  uint32_t _lastBitTime;
  uint8_t _bitCount;
  bool _isValid;
  uint32_t _cardId;

  friend class RfidState;
  friend class IdleState;
  friend class ReceivingState;
  friend class ProcessingState;
};

class RfidState
{
public:
  virtual ~RfidState() = default;
  virtual void handleEvent(RfidCommunication &rfid, RfidCommunication::Event event) = 0;
};

class IdleState : public RfidState
{
public:
  void handleEvent(RfidCommunication &rfid, RfidCommunication::Event event) override;
};

class ReceivingState : public RfidState
{
public:
  void handleEvent(RfidCommunication &rfid, RfidCommunication::Event event) override;
};

class ProcessingState : public RfidState
{
public:
  void handleEvent(RfidCommunication &rfid, RfidCommunication::Event event) override;
};

#endif // RFID_COMMUNICATION_HPP