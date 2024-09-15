#include "BSP.hpp"

void initBSP()
{
  // Initialize RFID pins
  pinMode(BSP::RFID_PIN_DATA_0, INPUT_PULLUP);
  pinMode(BSP::RFID_PIN_DATA_1, INPUT_PULLUP);
  pinMode(BSP::RFID_PIN_CP, INPUT_PULLUP);

  // Initialize terminal control pin
  pinMode(BSP::TERMINAL_PIN, OUTPUT);
  pinMode(BSP::WATER_PIN, OUTPUT);
  pinMode(BSP::ELECTRICITY_PIN, OUTPUT);
}
