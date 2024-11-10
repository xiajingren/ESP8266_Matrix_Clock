#ifndef Light_h
#define Light_h

#define ADC_PIN 17

class Light
{
private:
    unsigned long lastTime = 0;

public:
    void loop();
};

#endif