#pragma once

#include <Arduino.h>

extern IPAddress switcherIp;

void loadSwitcherIp();
void changeSwitcherIp(String newIp);