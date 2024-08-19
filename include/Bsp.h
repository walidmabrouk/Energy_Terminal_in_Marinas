#ifndef BSP_H
#define BSP_H

#include <Arduino.h>
#include <LittleFS.h>
#include "../lib/Business/Authentication/Authentication.hpp"

#define RFID_PIN_Data_0 36
#define RFID_PIN_Data_1 39
#define RFID_PIN_CP 34

void initBSP();
bool authenticate();

#endif // BSP_H
