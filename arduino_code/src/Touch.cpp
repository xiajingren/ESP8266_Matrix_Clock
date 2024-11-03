#include "Arduino.h"
#include "OneButton.h"

#include "Touch.h"

#define TOUCH_PIN 15

OneButton button(TOUCH_PIN, false, false);

Touch::Touch()
{
}

void onClick()
{
    Serial.println("onClick");
}

void onDoubleClick()
{
    Serial.println("onDoubleClick");
}

void onDuringLongPress()
{
    Serial.println("onDuringLongPress");
}

void onIdle()
{
    Serial.println("onIdle");
}

void onLongPressStart()
{
    Serial.println("onLongPressStart");
}

void onLongPressStop()
{
    Serial.println("onLongPressStop");
}

void onMultiClick()
{
    Serial.println("onMultiClick");
}

void onPress()
{
    Serial.println("onPress");
}

void Touch::setup()
{
    button.attachClick(onClick);
    button.attachDoubleClick(onDoubleClick);
    button.attachDuringLongPress(onDuringLongPress);
    button.attachIdle(onIdle);
    button.attachLongPressStart(onLongPressStart);
    button.attachLongPressStop(onLongPressStop);
    button.attachMultiClick(onMultiClick);
    button.attachPress(onPress);
}

void Touch::loop()
{
    button.tick();
}