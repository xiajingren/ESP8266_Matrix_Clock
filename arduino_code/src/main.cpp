#include <Arduino.h>

#include "Wifi.h"
#include "Led.h"
#include "_Time.h"
#include "Humiture.h"
#include "Touch.h"
#include "Light.h"

Wifi wifi;
_Time _time;
Humiture humiture;
Touch touch;
Light light;

void setup()
{
  Serial.println("start...");

  Serial.begin(115200);

  Led::setup();
  wifi.setup();
  _time.setup();
  humiture.setup();
  touch.setup();
}

void loop()
{
  _time.display();
  humiture.display();
  touch.loop();
  light.loop();
}