#ifndef Contorller_h
#define Contorller_h

#include "LedControl.h"
#include "RTClib.h"

class Contorller
{
private:
    // MAX7219矩阵屏控制引脚
    int DIN_PIN = 13;
    int CLK_PIN = 14;
    int CS_PIN = 12;

    int MaxDevices = 4;

    LedControl lc = LedControl(DIN_PIN, CLK_PIN, CS_PIN, MaxDevices);

    int position = 0;

    void initMatrix();
    void setIntensity(int intensity);

    void displayHumiture();
    size_t getHumitureContent(float temperature, float humidity, byte *content);

    void displayTime();
    size_t getTimeContent(DateTime dt, byte *content);

    void displayDate();
    size_t getDateContent(DateTime dt, byte *content);

    void copyToContent(size_t &index, byte *content, const byte *fonts, size_t size);
    void makeSpace(size_t &index, byte *content, size_t count = 1);
    void makeNumber(size_t &index, byte *content, float data, signed char width = 0, unsigned char prec = 0, unsigned char numberStyle = 0);

    void scrollLeft(byte *content, size_t size);

public:
    void setup();
    void loop();
};

#endif
