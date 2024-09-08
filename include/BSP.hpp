// BSP.hpp
#ifndef BSP_HPP
#define BSP_HPP

#include <Arduino.h>

namespace BSP
{
  constexpr int RFID_PIN_DATA_0 = 36;
  constexpr int RFID_PIN_DATA_1 = 39;
  constexpr int RFID_PIN_CP     = 19;

  constexpr int TERMINAL_PIN    = 23;
  constexpr int WATER_PIN       = 22;
  constexpr int ELECTRICITY_PIN = 21;
}

void initBSP();

#endif // BSP_HPP
