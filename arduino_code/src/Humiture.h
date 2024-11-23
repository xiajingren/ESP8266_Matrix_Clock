#ifndef Humiture_h
#define Humiture_h

class Humiture
{
private:
    unsigned long lastTime;

public:
    float temperature = 0.0f;
    float humidity = 0.0f;

    void setup();

    void loop();
};

#endif