#pragma once

#define PROGRAM_LED 2 // = D4
#define PREVIEW_LED 0 // = D3
#define STATUS_LED 4  // = D2

void configLedAnimation();
void blinkStatusLed(int times);