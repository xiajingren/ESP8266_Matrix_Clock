#include "Led.h"

Led::Led() {}

int Led::MaxDevices = 4;
LedControl Led::lc = LedControl(CONST_DIN_PIN, CONST_CLK_PIN, CONST_CS_PIN, MaxDevices);

void Led::setup()
{
    for (int i = 0; i < Led::MaxDevices; i++)
    {
        Led::lc.shutdown(i, false); // 取消关闭模式
        Led::lc.setIntensity(i, 8); // 设置亮度
        Led::lc.clearDisplay(i);    // 清除显示
    }
}

void Led::setRow(int addr, int row, byte value)
{
    Led::lc.setRow(addr, row, value);
}