#include "memory.h"

#include <EEPROM.h>

IPAddress switcherIp(192, 168, 131, 8);

const int EEPROM_ADRESS_SWITCHER_IP = 0;

void loadSwitcherIp()
{
  EEPROM.begin(512);
  EEPROM.get(EEPROM_ADRESS_SWITCHER_IP, switcherIp);
  EEPROM.end();
}	

void changeSwitcherIp(String newIp)
{
  switcherIp.fromString(newIp);

  EEPROM.begin(512);
  EEPROM.put(EEPROM_ADRESS_SWITCHER_IP, switcherIp);
  EEPROM.commit();
  EEPROM.end();
}