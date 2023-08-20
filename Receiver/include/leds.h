#pragma once

#define PROGRAM_LED 2 // = D4
#define PREVIEW_LED 0 // = D3
#define STATUS_LED 4  // = D2

#define PROGRAM_BRIGHTNESS 1000  // = D2
#define PREVIEW_BRIGHTNESS 20  // = D2
#define STATUS_BRIGHTNESS  10  // = D2

#define PWMFREQ 1000 // PWM frequency in Hz
#define PWMRES 1023 // PWM resolution

void configLedAnimation();
void blinkStatusLed(int times, int delayTime=1000);