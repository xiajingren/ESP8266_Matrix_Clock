#include "Led.h"

Led::Led()
{
}

void Led::setup()
{
    for (int i = 0; i < MaxDevices; i++)
    {
        lc.shutdown(i, false); // 取消关闭模式
        lc.setIntensity(i, 8); // 设置亮度
        lc.clearDisplay(i);    // 清除显示
    }
}

void Led::setRow(int addr, int row, byte value)
{
    lc.setRow(addr, row, value);
}
