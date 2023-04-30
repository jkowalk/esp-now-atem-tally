#pragma once

#define CAMERA_ID_ADDRESS 0

extern int camId;

// load the camera id from the eeprom memory
void loadCameraId();

// save the camera id to the eeprom memory
void saveCameraId();