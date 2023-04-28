#include <Arduino.h>

#include "configWebserver.h"
#include "tallyCommunication.h"
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
  digitalWrite(STATUS_LED, LOW);

  pinMode(CONFIG_BUTTON, INPUT_PULLDOWN_16);

  loadCameraId();

  delay(500);
  blinkStatusLed(camId);
  delay(500);

  if (digitalRead(CONFIG_BUTTON) == HIGH)
  {
    Serial.println("Config mode activated");
    configMode = true;
    startConfigWebserver();

    return;
  }

  setupEspNow();
  digitalWrite(STATUS_LED, HIGH);
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
