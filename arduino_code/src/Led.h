#ifndef Led_h
#define Led_h

#include <LedControl.h>
#include "Const.h"

class Led
{
private:
    const int MaxDevices = 4;
    LedControl lc = LedControl(CONST_DIN_PIN, CONST_CLK_PIN, CONST_CS_PIN, MaxDevices);

public:
    Led();

    void setup();

    void setRow(int addr, int row, byte value);
};

#endif