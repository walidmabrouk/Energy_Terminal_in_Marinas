#ifndef BSP_HPP
#define BSP_HPP

#include <Arduino.h>
#include <LittleFS.h>
#include "../lib/Business/Authentication/Authentication.hpp"

namespace BSP
{
  // Pin definitions for RFID
  constexpr int RFID_PIN_DATA_0 = 36;
  constexpr int RFID_PIN_DATA_1 = 39;
  constexpr int RFID_PIN_CP = 34;

  // Pin definitions for other components
  constexpr int TERMINAL_PIN = 1;
  constexpr int WATER_PIN = 2;
  constexpr int ELECTRICITY_PIN = 3;
}

// Initialization function for the board support package
void initBSP();

// Authentication function declaration
bool authenticate();

#endif // BSP_HPP
