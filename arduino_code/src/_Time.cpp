#include "_Time.h"

#include <NTPClient.h>
#include <WiFiUdp.h>
#include <ESP8266WiFi.h>
#include "SPI.h"

// 定义NTP客户端以获取时间
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "ntp.aliyun.com", 8 * 3600);

RTC_DS3231 rtc;

void _Time::setup()
{
    Serial.println("_Time setup");
    timeClient.begin();

    if (!rtc.begin())
    {
        Serial.println("Couldn't find RTC");
        Serial.flush();
        while (1)
            delay(10);
    }
    if (rtc.lostPower())
    {
        Serial.println("RTC lost power, let's set the time!");
        // When time needs to be set on a new device, or after a power loss, the
        // following line sets the RTC to the date & time this sketch was compiled
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
        // This line sets the RTC with an explicit date & time, for example to set
        // January 21, 2014 at 3am you would call:
        // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
    }
}

void _Time::loop()
{
    unsigned long currentTime = millis();

    if (lastTime > 0 && currentTime - lastTime < 1000)
        return;

    lastTime = currentTime;

    now = rtc.now();

    if (lastSyncTime == 0 && currentTime - lastSyncTime > 15000)
    {
        Serial.println("Sync time from NTP");
        timeClient.update();
        rtc.adjust(DateTime(timeClient.getEpochTime()));

        lastSyncTime = currentTime;
    }
}
