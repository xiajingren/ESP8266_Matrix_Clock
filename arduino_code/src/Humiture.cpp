#include "Humiture.h"

#include "DHT.h"

#define DHTPIN 2 // 16
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void Humiture::setup()
{
    Serial.println(F("DHTxx setup!"));

    dht.begin();
}

void Humiture::loop()
{
    unsigned long currentTime = millis();

    if (lastTime > 0 && currentTime - lastTime < 10000)
        return;

    lastTime = currentTime;

    temperature = dht.readTemperature();
    humidity = dht.readHumidity();
}
