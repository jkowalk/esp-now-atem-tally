#include "memory.h"

#include <Arduino.h>
#include <EEPROM.h>

int camId = 0;

void loadCameraId()
{
  EEPROM.begin(512);
  EEPROM.get(CAMERA_ID_ADDRESS, camId);
  EEPROM.commit();
  Serial.println("Camera ID: " + String(camId));
}

void saveCameraId()
{
  EEPROM.begin(512);
  EEPROM.put(CAMERA_ID_ADDRESS, camId);
  EEPROM.commit();
}