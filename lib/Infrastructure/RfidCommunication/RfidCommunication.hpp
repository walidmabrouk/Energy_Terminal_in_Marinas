#ifndef RFID_COMMUNICATION_HPP
#define RFID_COMMUNICATION_HPP

#include <Arduino.h>
#include "../lib/Domain/Services/InfrastructureServices/IRfidCommunication/IRfidCommunication.hpp"

enum class RfidState
{
  IDLE,
  CARD_DETECTED,
  STATE_ZERO,
  STATE_ONE,
  RECEPTION_COMPLETE,
  FRAME_VERIFIED,
  CODE_RECEIVED
};

class RfidCommunication : public IRfidCommunication // Ensure you use 'public' inheritance
{
private:
  RfidState currentState;
  bool flagD0;
  bool flagD1;
  bool flagCP;
  bool TrameIsOK;
  int frameIndex;
  int tab[26];

  void handleIdle();
  void handleCardDetected();
  void handleStateZero();
  void handleStateOne();
  void handleReceptionComplete();
  void handleFrameVerified();
  void delay250ms();
  void delay800us();
  bool checkEvenParity(int start, int end);
  bool checkOddParity(int start, int end);

public:
  RfidCommunication();
  void update();
  void reset();

  bool isCardDetected();
  bool isStateZero();
  bool isStateOne();
  bool isFrameVerified();
  std::string readRFID() const;
};

#endif // RFID_COMMUNICATION_HPP
