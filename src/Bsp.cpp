#include "bsp.h"

void initBSP()
{
  // Initialize any hardware components or pins here
  pinMode(RFID_PIN_Data_0, INPUT_PULLUP);
  pinMode(RFID_PIN_Data_1, INPUT_PULLUP);
  pinMode(RFID_PIN_CP, OUTPUT);
}
