#ifndef _Time_h
#define _Time_h

#include "RTClib.h"

class _Time
{
private:
    unsigned long lastTime = 0;
    unsigned long lastSyncTime = 0;

public:
    DateTime now;

    void setup();
    void loop();
};

#endif