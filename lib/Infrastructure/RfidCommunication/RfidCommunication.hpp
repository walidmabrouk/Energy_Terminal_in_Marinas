#ifndef RFID_COMMUNICATION_HPP
#define RFID_COMMUNICATION_HPP

#include <Arduino.h>
#include "../../Domain/Services/InfrastructureServices/IRfidCommunication/IRfidCommunication.hpp"
#include "../../Domain/Services/InfrastructureServices/IDigital/IDigital.hpp"
#include "../../include/BSP.hpp"

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

class RfidCommunication : public IRfidCommunication
{
private:
  RfidState currentState;
  IDigital &digital;
  volatile bool flagD0;
  volatile bool flagD1;
  bool flagCP;
  bool TrameIsOK;
  int frameIndex;
  int tab[26];


  void handleIdle();
  void handleCardDetected();
  void handleStateZero();
  void handleStateOne();
  void handleReceptionComplete();
  bool handleFrameVerified();
  void delay250ms();
  void delay800us();
  bool checkEvenParity(int start, int end);
  bool checkOddParity(int start, int end);

public:
  explicit RfidCommunication(IDigital &digital);
  ~RfidCommunication() override;

  void update() override;
  void reset() override;
  bool isCardDetected() override;
  bool isStateZero() override;
  bool isStateOne() override;
  std::string readRFID() const override;
};

#endif // RFID_COMMUNICATION_HPP