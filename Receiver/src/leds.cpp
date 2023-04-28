#include "leds.h"
#include <Arduino.h>

int led_animation = 0;
long last_led_animation = millis();

void configLedAnimation()
{
  if (millis() - last_led_animation > 1000)
  {
    last_led_animation = millis();
    switch (led_animation)
    {
    case 0:
      digitalWrite(PROGRAM_LED, HIGH);
      digitalWrite(PREVIEW_LED, LOW);
      digitalWrite(STATUS_LED, LOW);
      break;
    case 1:
      digitalWrite(PROGRAM_LED, LOW);
      digitalWrite(PREVIEW_LED, HIGH);
      digitalWrite(STATUS_LED, LOW);
      break;
    case 2:
      digitalWrite(PROGRAM_LED, LOW);
      digitalWrite(PREVIEW_LED, LOW);
      digitalWrite(STATUS_LED, HIGH);
      break;
    }
    led_animation++;
    if (led_animation >= 3)
      led_animation = 0;
  }
}

void blinkStatusLed(int times)
{
  for (int i = 0; i < times; i++)
  {
    digitalWrite(STATUS_LED, HIGH);
    delay(1000);
    digitalWrite(STATUS_LED, LOW);
    delay(1000);
  }
}