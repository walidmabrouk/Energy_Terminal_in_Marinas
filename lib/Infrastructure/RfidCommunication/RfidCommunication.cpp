#include "RfidCommunication.hpp"

RfidCommunication *RfidCommunication::_instance = nullptr;

RfidCommunication::RfidCommunication(BSP &bsp, uint8_t data0Pin, uint8_t data1Pin, uint8_t cpPin)
    : _bsp(bsp), _data0Pin(data0Pin), _data1Pin(data1Pin), _cpPin(cpPin),
      _currentState(new IdleState()), _currentStateId(StateId::IDLE),
      _cardData(0), _lastBitTime(0), _isValid(false), _cardId(0), _bitCount(0)
{
  _instance = this;
}

void RfidCommunication::begin()
{
  _bsp.pinMode(_data0Pin, INPUT_PULLUP);
  _bsp.pinMode(_data1Pin, INPUT_PULLUP);
  _bsp.pinMode(_cpPin, INPUT_PULLUP);
  _bsp.attachInterrupt(_data0Pin, data0Interrupt, FALLING);
  _bsp.attachInterrupt(_data1Pin, data1Interrupt, FALLING);
  _bsp.attachInterrupt(_cpPin, cpInterrupt, FALLING);
}

void RfidCommunication::handleEvent(Event event)
{
  _currentState->handleEvent(*this, event);
}

bool RfidCommunication::isCardDetected() const
{
  return _currentStateId == StateId::PROCESSING;
}

uint32_t RfidCommunication::getCardId() const
{
  return _cardId;
}

bool RfidCommunication::isValid() const
{
  return _isValid;
}

void IRAM_ATTR RfidCommunication::data0Interrupt()
{
  if (_instance)
  {
    _instance->addBit(0);
  }
}

void IRAM_ATTR RfidCommunication::data1Interrupt()
{
  if (_instance)
  {
    _instance->addBit(1);
  }
}

void IRAM_ATTR RfidCommunication::cpInterrupt()
{
  if (_instance)
  {
    _instance->handleEvent(Event::CARD_DETECTED);
  }
}

void RfidCommunication::addBit(bool bit)
{
  if (_bitCount < WIEGAND_BIT_COUNT)
  {
    _cardData <<= 1;
    _cardData |= bit ? 1 : 0;
    _bitCount++;
    _lastBitTime = _bsp.millis();

    if (_bitCount == WIEGAND_BIT_COUNT)
    {
      handleEvent(Event::BIT_RECEIVED);
    }
  }
}

bool RfidCommunication::validateParity()
{
  uint64_t data = _cardData & 0x3FFFFFFFFULL; // 34 bits
  bool evenParity = (_cardData >> 33) & 1;
  bool oddParity = _cardData & 1;

  uint8_t calculatedEvenParity = 0;
  uint8_t calculatedOddParity = 1; // Initialize to 1 for odd parity

  // Calculate even parity (bits 2-17)
  for (int i = 1; i <= 16; i++)
  {
    calculatedEvenParity ^= (data >> (32 - i)) & 1;
  }

  // Calculate odd parity (bits 18-33)
  for (int i = 17; i <= 32; i++)
  {
    calculatedOddParity ^= (data >> (32 - i)) & 1;
  }

  _bsp.println("Parity Validation Details:");
  _bsp.printf("Received Even Parity: %d, Calculated: %d\n", evenParity, calculatedEvenParity);
  _bsp.printf("Received Odd Parity: %d, Calculated: %d\n", oddParity, calculatedOddParity);
  _bsp.printf("Even Parity Valid: %s, Odd Parity Valid: %s\n",
              evenParity == calculatedEvenParity ? "Yes" : "No",
              oddParity == calculatedOddParity ? "Yes" : "No");

  return (evenParity == calculatedEvenParity) && (oddParity == calculatedOddParity);
}

void RfidCommunication::changeState(RfidState *newState, StateId newStateId)
{
  delete _currentState;
  _currentState = newState;
  _currentStateId = newStateId;
}

void IdleState::handleEvent(RfidCommunication &rfid, RfidCommunication::Event event)
{
  switch (event)
  {
  case RfidCommunication::Event::BIT_RECEIVED:
    rfid.changeState(new ReceivingState(), RfidCommunication::StateId::RECEIVING);
    break;
  case RfidCommunication::Event::CARD_DETECTED:
    rfid._bsp.println("Card detected in idle state");
    break;
  default:
    break;
  }
}

void ReceivingState::handleEvent(RfidCommunication &rfid, RfidCommunication::Event event)
{
  switch (event)
  {
  case RfidCommunication::Event::BIT_RECEIVED:
    if (rfid._bitCount == RfidCommunication::WIEGAND_BIT_COUNT)
    {
      rfid.changeState(new ProcessingState(), RfidCommunication::StateId::PROCESSING);
      rfid.handleEvent(RfidCommunication::Event::TIMEOUT);
    }
    break;
  case RfidCommunication::Event::TIMEOUT:
    if (rfid._bsp.millis() - rfid._lastBitTime >= RfidCommunication::TIMEOUT_MS)
    {
      rfid.changeState(new ProcessingState(), RfidCommunication::StateId::PROCESSING);
      rfid.handleEvent(RfidCommunication::Event::TIMEOUT);
    }
    break;
  default:
    break;
  }
}

void ProcessingState::handleEvent(RfidCommunication &rfid, RfidCommunication::Event event)
{
  switch (event)
  {
  case RfidCommunication::Event::TIMEOUT:
    rfid._bsp.printf("Complete bits received: %010llX\n", rfid._cardData);

    rfid._isValid = rfid.validateParity();
    if (rfid._isValid)
    {
      rfid._cardId = (rfid._cardData >> 1) & 0xFFFFFFFF; // Extract 32-bit card ID
      rfid._bsp.println("Valid tag detected!");
      rfid._bsp.printf("Card ID: %u (0x%08X)\n", rfid._cardId, rfid._cardId);
    }
    else
    {
      rfid._bsp.println("Parity error, invalid tag.");
      rfid.handleEvent(RfidCommunication::Event::INVALID_PARITY);
    }
    rfid._bitCount = 0;
    rfid._cardData = 0;
    rfid.changeState(new IdleState(), RfidCommunication::StateId::IDLE);
    break;
  case RfidCommunication::Event::INVALID_PARITY:
    rfid._cardId = 0;
    rfid._isValid = false;
    break;
  default:
    break;
  }
}