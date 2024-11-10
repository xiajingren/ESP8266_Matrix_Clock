#include "Light.h"
#include "Arduino.h"

#include "Led.h"

void Light::loop()
{
    unsigned long currentTime = millis();

    if (lastTime > 0 && currentTime - lastTime < 1000)
        return;

    lastTime = currentTime;

    int sensorValue = analogRead(ADC_PIN);

    if (sensorValue > 1000)
    {
        Led::setIntensity(14);
    }
    else if (sensorValue > 800)
    {
        Led::setIntensity(12);
    }
    else if (sensorValue > 600)
    {
        Led::setIntensity(10);
    }
    else if (sensorValue > 400)
    {
        Led::setIntensity(8);
    }
    else if (sensorValue > 200)
    {
        Led::setIntensity(6);
    }
    else
    {
        Led::setIntensity(2);
    }

    Serial.println("sen:" + String(sensorValue));
}