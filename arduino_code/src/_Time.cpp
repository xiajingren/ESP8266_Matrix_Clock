#include "_Time.h"

#include <NTPClient.h>
#include <WiFiUdp.h>

#include "RTClib.h"
#include "SPI.h"

#include "Font.h"

#include "Led.h"

// 定义NTP客户端以获取时间
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "ntp.aliyun.com", 8 * 3600);

RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

_Time::_Time()
{
}

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

DateTime getTimeFromRTC()
{
    DateTime now = rtc.now();

    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();

    Serial.print(" since midnight 1/1/1970 = ");
    Serial.print(now.unixtime());
    Serial.print("s = ");
    Serial.print(now.unixtime() / 86400L);
    Serial.println("d");

    // calculate a date which is 7 days, 12 hours, 30 minutes, 6 seconds into the future
    DateTime future(now + TimeSpan(7, 12, 30, 6));

    Serial.print(" now + 7d + 12h + 30m + 6s: ");
    Serial.print(future.year(), DEC);
    Serial.print('/');
    Serial.print(future.month(), DEC);
    Serial.print('/');
    Serial.print(future.day(), DEC);
    Serial.print(' ');
    Serial.print(future.hour(), DEC);
    Serial.print(':');
    Serial.print(future.minute(), DEC);
    Serial.print(':');
    Serial.print(future.second(), DEC);
    Serial.println();

    Serial.print("Temperature: ");
    Serial.print(rtc.getTemperature());
    Serial.println(" C");

    Serial.println();

    return now;
}

void _Time::display()
{
    unsigned long currentTime = millis();

    if (lastTime > 0 && currentTime - lastTime < 1000)
        return;

    getTimeFromRTC();

    lastTime = currentTime;

    timeClient.update();

    int h = timeClient.getHours();
    int m = timeClient.getMinutes();
    int s = timeClient.getSeconds();

    Serial.println(String(h) + ":" + String(m) + ":" + String(s));

    for (int row = 0; row < 8; row++)
    {
        byte h1 = NumberFonts[h / 10][row];
        byte h2 = NumberFonts[h % 10][row];

        byte dot = NumberFonts[10][row];

        byte m1 = NumberFonts[m / 10][row];
        byte m2 = NumberFonts[m % 10][row];

        byte s1 = MinNumberFonts[s / 10][row];
        byte s2 = MinNumberFonts[s % 10][row];

        byte row_data1 = h1 | (h2 >> 5);
        byte row_data2 = (h2 << 3) | (dot >> 2) | (m1 >> 4);
        byte row_data3 = (m2 >> 1);
        byte row_data4 = (s1 >> 1) | (s2 >> 5);

        Led::setRow(0, row, row_data1);
        Led::setRow(1, row, row_data2);
        Led::setRow(2, row, row_data3);
        Led::setRow(3, row, row_data4);
    }
}
