#include "Contorller.h"

#include "Font.h"
#include "Arduino.h"

void Contorller::setup()
{
    initMatrix();
}

void Contorller::loop()
{
    // displayHumiture();
    displayTime();
    // displayDate();

    // lc.setColumn(0, 0, B00000001);
    // lc.setColumn(1, 1, B01000001);
    // lc.setColumn(2, 2, B01100011);
    // lc.setColumn(3, 3, B01110111);

    delay(100);
}

void Contorller::initMatrix()
{
    for (int i = 0; i < MaxDevices; i++)
    {
        lc.shutdown(i, false); // 取消关闭模式
        lc.setIntensity(i, 8); // 设置亮度
        lc.clearDisplay(i);    // 清除显示
    }
}
void Contorller::setIntensity(int intensity)
{
    for (int i = 0; i < MaxDevices; i++)
    {
        lc.setIntensity(i, intensity); // 设置亮度
    }
}

void Contorller::displayHumiture()
{
    float t = -23.60;
    float h = -45.50;

    byte content[100];
    size_t size = getHumitureContent(t, h, content);

    scrollLeft(content, size);
}

size_t Contorller::getHumitureContent(float temperature, float humidity, byte *content)
{
    size_t index = 0;

    makeNumber(index, content, temperature, 0, 1);
    makeSpace(index, content);
    copyToContent(index, content, Fonts_Char1[1], sizeof(Fonts_Char1[1]));

    makeSpace(index, content, 6);

    makeNumber(index, content, humidity, 0, 1);
    makeSpace(index, content);
    copyToContent(index, content, Fonts_Char1[2], sizeof(Fonts_Char1[2]));

    return index;
}

void Contorller::makeSpace(size_t &index, byte *content, size_t count)
{
    for (size_t i = 0; i < count; i++)
    {
        copyToContent(index, content, Fonts_Char2[0], sizeof(Fonts_Char2[0]));
    }
}

void Contorller::displayTime()
{
    DateTime dt = DateTime(2024, 1, 1, 12, 9, 20);

    byte content[32];
    getTimeContent(dt, content);

    for (int i = 0; i < MaxDevices; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            lc.setColumn(i, j, content[i * 8 + j]);
        }
    }
}

size_t Contorller::getTimeContent(DateTime dt, byte *content)
{
    uint8_t h = dt.hour();
    uint8_t m = dt.minute();
    uint8_t s = dt.second();

    size_t index = 0;

    makeNumber(index, content, h, 2);
    makeSpace(index, content);

    copyToContent(index, content, Fonts_Char2[2], sizeof(Fonts_Char2[2]));
    makeSpace(index, content);

    makeNumber(index, content, m, 2);
    makeSpace(index, content, 4);

    makeNumber(index, content, s, 2, 0, 1);

    Serial.println(index);

    return index;
}

void Contorller::displayDate()
{
    DateTime dt = DateTime(2024, 1, 2, 12, 10, 20);
    byte content[100];
    size_t size = getDateContent(dt, content);

    scrollLeft(content, size);
}

size_t Contorller::getDateContent(DateTime dt, byte *content)
{
    uint16_t y = dt.year();
    uint8_t m = dt.month();
    uint8_t d = dt.day();

    uint8_t w = dt.dayOfTheWeek();

    size_t index = 0;

    makeNumber(index, content, y);
    makeSpace(index, content);

    copyToContent(index, content, Fonts_Char1[0], sizeof(Fonts_Char1[0]));
    makeSpace(index, content);

    makeNumber(index, content, m, 2);
    makeSpace(index, content);

    copyToContent(index, content, Fonts_Char1[0], sizeof(Fonts_Char1[0]));
    makeSpace(index, content);

    makeNumber(index, content, d, 2);
    makeSpace(index, content, 8);

    switch (w)
    {
    case 0:
        copyToContent(index, content, Fonts_Week_Sun, sizeof(Fonts_Week_Sun));
        break;
    case 1:
        copyToContent(index, content, Fonts_Week_Mon, sizeof(Fonts_Week_Mon));
        break;
    case 2:
        copyToContent(index, content, Fonts_Week_Tue, sizeof(Fonts_Week_Tue));
        break;
    case 3:
        copyToContent(index, content, Fonts_Week_Wed, sizeof(Fonts_Week_Wed));
        break;
    case 4:
        copyToContent(index, content, Fonts_Week_Thu, sizeof(Fonts_Week_Thu));
        break;
    case 5:
        copyToContent(index, content, Fonts_Week_Fri, sizeof(Fonts_Week_Fri));
        break;
    case 6:
        copyToContent(index, content, Fonts_Week_Sat, sizeof(Fonts_Week_Sat));
        break;
    default:
        break;
    }

    return index;
}

void Contorller::copyToContent(size_t &index, byte *content, const byte *fonts, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        content[index++] = fonts[i];
    }
}

void Contorller::makeNumber(size_t &index, byte *content, float data, signed char width, unsigned char prec, unsigned char numberStyle)
{
    char temp[10];
    sprintf(temp, "%0*.*f", width, prec, data);

    Serial.println("ss1111:" + String(temp));

    for (size_t i = 0; i < sizeof(temp); i++)
    {
        if (temp[i] == '\0')
            break;

        if (i > 0)
            makeSpace(index, content);

        if (temp[i] == '-')
        {
            copyToContent(index, content, Fonts_Char1[0], sizeof(Fonts_Char1[0]));
        }
        else if (temp[i] == '.')
        {
            copyToContent(index, content, Fonts_Char2[1], sizeof(Fonts_Char2[1]));
        }
        else
        {
            if (numberStyle == 1)
                copyToContent(index, content, Fonts_Number2[temp[i] - '0'], sizeof(Fonts_Number2[temp[i] - '0']));
            else
                copyToContent(index, content, Fonts_Number1[temp[i] - '0'], sizeof(Fonts_Number1[temp[i] - '0']));
        }
    }
}

void Contorller::scrollLeft(byte *content, size_t size)
{
    for (int i = 0; i < MaxDevices; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            if (i * 8 + j - position < size)
            {
                lc.setColumn(i, j, content[i * 8 + j - position]);
            }
            else
            {
                lc.setColumn(i, j, 0);
            }
        }
    }

    position--;
    if (position < static_cast<int>(0 - size))
        position = MaxDevices * 8;
}
