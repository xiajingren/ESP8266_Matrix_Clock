#include "_Time.h"

#include <NTPClient.h>
#include <WiFiUdp.h>

#include "Font.h"

#include "Led.h"

// 定义NTP客户端以获取时间
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "ntp.aliyun.com", 8 * 3600);

_Time::_Time()
{
}

void _Time::setup()
{
    timeClient.begin();
}

void _Time::display()
{
    unsigned long currentTime = millis();

    if (lastTime > 0 && currentTime - lastTime < 1000)
        return;

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
