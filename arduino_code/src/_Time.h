#ifndef _Time_h
#define _Time_h

class _Time
{
private:
    unsigned long lastTime = 0;

public:
    _Time(/* args */);

    void setup();

    void display();
};

#endif