#include "Wifi.h"
#include <Arduino.h>
#include <ESP8266WiFi.h>

// 替换为你的网络凭据
const char *ssid = "1505";
const char *password = "13241178098";

Wifi::Wifi()
{
}

void Wifi::setup()
{
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
}
