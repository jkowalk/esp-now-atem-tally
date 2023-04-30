#include <Arduino.h>

#include "memory.h"
#include "atemConnection.h"
#include "espNow.h"
#include "configWebserver.h"

#define ERROR_LED_PIN 2

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    ;

  // Set LED pin to output mode
  pinMode(ERROR_LED_PIN, OUTPUT);
  digitalWrite(ERROR_LED_PIN, HIGH);

  loadSwitcherIp();

  setupWebserver();

  setupEspNow();

  setupAtemConnection();
}

void loop()
{
  webserverLoop();
  atemLoop();

  if (!atemIsConnected())
  {
    digitalWrite(ERROR_LED_PIN, HIGH);
  }
  else
  {
    digitalWrite(ERROR_LED_PIN, LOW);
  }
  
  if (checkForAtemChanges())
  {
    sendCurrentAtemState();
  }
  delay(5);
}