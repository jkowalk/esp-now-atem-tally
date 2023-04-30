#pragma once

#include <Arduino.h>

void setupEspNow();
void sendCurrentAtemState();
void sendMessage(boolean * program, boolean * preview, boolean transition, boolean request);