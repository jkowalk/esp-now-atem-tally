#pragma once

#include <Arduino.h>

void setupEspNow();
void sendCurrentAtemState();
void sendMessage(int program, int preview, boolean transition, boolean request);