#ifndef Contorller_h
#define Contorller_h

#include "LedControl.h"
#include "RTClib.h"

class Contorller
{
private:
    unsigned long lastTime = 0;

    void setIntensity(int intensity);

    void displayHumiture();
    size_t getHumitureContent(float temperature, float humidity, byte *content);

    void displayTime();
    size_t getTimeContent(DateTime dt, byte *content);

    void displayDate();
    size_t getDateContent(DateTime dt, byte *content);

    void copyToContent(size_t &index, byte *content, const byte *fonts, size_t size);
    void makeSpace(size_t &index, byte *content, size_t count = 1);
    void makeNumber(size_t &index, byte *content, float data, signed char width = 0, unsigned char prec = 0, unsigned char numberStyle = 0);

    void scrollLeft(byte *content, size_t size);

    static void initMatrix();
    static void shutdownMatrix();
    static void onPress();
    static void onLongPressStart();

public:
    void setup();
    void loop();
};

#endif
