#include <Arduino.h>

#include "Wifi.h"

#include "Led.h"

#include "_Time.h"

Wifi wifi;
Led led;
_Time _time;

void setup()
{
  Serial.println("start...");

  Serial.begin(115200);

  led.setup();
  wifi.setup();
  _time.setup();
}

void loop()
{
  _time.display(led);

  delay(1000);
}