#include "Contorller.h"

#include "Font.h"
#include "Arduino.h"

void Contorller::setup()
{
    initMatrix();
}

void Contorller::loop()
{
    displayHumiture();

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

    byte b[100];
    size_t s = getHumitureContent(t, h, b);

    position--;
    if (position < static_cast<int>(0 - s))
        position = MaxDevices * 8;

    for (int i = 0; i < MaxDevices; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            if (i * 8 + j - position < s)
            {
                lc.setColumn(i, j, b[i * 8 + j - position]);
            }
            else
            {
                lc.setColumn(i, j, 0);
            }
        }
    }
}

size_t Contorller::getHumitureContent(float temperature, float humidity, byte *content)
{
    size_t index = 0;
    size_t s = 0;
    byte temp[50];

    s = getFloatContent(temperature, temp);
    for (size_t i = 0; i < s; i++)
    {
        content[index++] = temp[i];
    }

    for (size_t j = 0; j < sizeof(NumberFontsV2[11]); j++)
    {
        content[index++] = NumberFontsV2[11][j];
    }
    index = markSpace(index, content, 6);

    s = getFloatContent(humidity, temp);
    for (size_t i = 0; i < s; i++)
    {
        content[index++] = temp[i];
    }

    for (size_t j = 0; j < sizeof(NumberFontsV2[12]); j++)
    {
        content[index++] = NumberFontsV2[12][j];
    }
    index = markSpace(index, content);

    return index;
}

size_t Contorller::getFloatContent(float data, byte *content)
{
    char temp[10];
    dtostrf(data, 0, 1, temp);

    size_t index = 0;
    for (size_t i = 0; i < sizeof(temp); i++)
    {
        if (temp[i] == '\0')
            break;

        if (temp[i] == '-')
        {
            for (size_t j = 0; j < sizeof(NumberFontsV2[10]); j++)
            {
                content[index++] = NumberFontsV2[10][j];
            }
            index = markSpace(index, content);
        }
        else if (temp[i] == '.')
        {
            content[index++] = 1;
            index = markSpace(index, content);
        }
        else
        {
            for (size_t j = 0; j < sizeof(NumberFontsV2[temp[i] - '0']); j++)
            {
                content[index++] = NumberFontsV2[temp[i] - '0'][j];
            }
            index = markSpace(index, content);
        }
    }

    return index;
}

size_t Contorller::markSpace(size_t index, byte *content, size_t length)
{
    for (size_t i = 0; i < length; i++)
    {
        content[index + i] = 0;
    }
    return index + length;
}
