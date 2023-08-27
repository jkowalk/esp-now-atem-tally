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
      analogWrite(PROGRAM_LED, PROGRAM_BRIGHTNESS);
      analogWrite(PREVIEW_LED, 0);
      analogWrite(STATUS_LED, 0);
      break;
    case 1:
      analogWrite(PROGRAM_LED, 0);
      analogWrite(PREVIEW_LED, PREVIEW_BRIGHTNESS);
      analogWrite(STATUS_LED, 0);
      break;
    case 2:
      analogWrite(PROGRAM_LED, 0);
      analogWrite(PREVIEW_LED, 0);
      analogWrite(STATUS_LED, STATUS_BRIGHTNESS);
      break;
    }
    led_animation++;
    if (led_animation >= 3)
      led_animation = 0;
  }
}

void blinkStatusLed(int times, int delayTime)
{
  for (int i = 0; i < times; i++)
  {
    analogWrite(STATUS_LED, STATUS_BRIGHTNESS);
    delay(delayTime);
    analogWrite(STATUS_LED, 0);
    delay(delayTime);
  }
}