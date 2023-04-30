#pragma once

#include <Arduino.h>

boolean atemIsConnected();
void setupAtemConnection();
void atemLoop();
boolean checkForAtemChanges();
int getProgramInput();
int getPreviewInput();
boolean * getProgramTallyArray();
boolean * getPreviewTallyArray();
boolean getTransition();
String getATEMInformation();