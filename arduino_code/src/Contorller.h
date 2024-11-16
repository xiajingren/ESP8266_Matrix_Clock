#ifndef Contorller_h
#define Contorller_h

#include "LedControl.h"

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
    size_t getFloatContent(float data, byte *content);
    size_t markSpace(size_t index, byte *content, size_t length = 1);

public:
    void setup();
    void loop();
};

#endif
