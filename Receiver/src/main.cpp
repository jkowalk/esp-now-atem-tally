#include <Arduino.h>

#include "configWebserver.h"
#include "espNowReceiver.h"
#include "leds.h"
#include "memory.h"

#define CONFIG_BUTTON 13 // = D7

boolean configMode = false;

void setup()
{
  Serial.begin(115200);
  Serial.println();

  pinMode(PROGRAM_LED, OUTPUT);
  pinMode(PREVIEW_LED, OUTPUT);
  pinMode(STATUS_LED, OUTPUT);

  analogWriteFreq(PWMFREQ); // Set PWM frequency
  analogWriteRange(PWMRES); // Set PWM resolution

  analogWrite(STATUS_LED, 0);

  pinMode(CONFIG_BUTTON, INPUT_PULLDOWN_16);

  loadCameraId();

  // Let status LED blink as often as Cam Id (max 10)
  blinkStatusLed(3, 100);
  delay(500);
  blinkStatusLed(min(10, camId), 400);
  delay(500);

  if (digitalRead(CONFIG_BUTTON) == HIGH)
  {
    Serial.println("Config mode activated");
    configMode = true;
    startConfigWebserver();

    return;
  }

  setupEspNow();
  analogWrite(STATUS_LED, STATUS_BRIGHTNESS);
}

void loop()
{
  if (configMode)
  {
    configWebserverLoop();
    return;
  }

  espNowLoop();
}
