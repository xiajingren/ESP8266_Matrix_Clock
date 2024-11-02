#ifndef Led_h
#define Led_h

#include <Pin.h>
#include <LedControl.h>

const int MaxDevices = 4;

class Led
{
private:
    LedControl lc = LedControl(DIN_PIN, CLK_PIN, CS_PIN, MaxDevices);

public:
    Led();

    void setup();

    void setRow(int addr, int row, byte value);

    // ~Led();
};

#endif