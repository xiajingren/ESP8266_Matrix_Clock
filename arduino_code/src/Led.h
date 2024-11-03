#ifndef Led_h
#define Led_h

#include <LedControl.h>
#include "Const.h"

class Led
{
private:
    Led();
    static int MaxDevices;
    static LedControl lc;

public:
    static void setup();

    static void setRow(int addr, int row, byte value);
};

#endif