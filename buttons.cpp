#include "buttons.h"

#include "config.h"
#include "globals.h"

static bool upPressed = false;
static bool downPressed = false;
static bool selectPressed = false;

static bool lastUpReading = BUTTON_RELEASED;
static bool lastDownReading = BUTTON_RELEASED;
static bool lastSelectReading = BUTTON_RELEASED;

static bool stableUpState = BUTTON_RELEASED;
static bool stableDownState = BUTTON_RELEASED;
static bool stableSelectState = BUTTON_RELEASED;

static unsigned long lastUpChange = 0;
static unsigned long lastDownChange = 0;
static unsigned long lastSelectChange = 0;

static void updateButton(uint8_t pin, bool &lastReading, bool &stableState, bool &pressedEvent, unsigned long &lastChange, unsigned long now)
{
    bool currentReading = digitalRead(pin);

    if (currentReading != lastReading)
    {
        lastChange = now;
        lastReading = currentReading;
    }

    if ((now - lastChange) < BUTTON_DEBOUNCE_INTERVAL)
        return;

    if (currentReading == stableState)
        return;

    stableState = currentReading;

    if (stableState == BUTTON_PRESSED)
    {
        pressedEvent = true;
        lastButtonPress = now;
    }
}

void initializeButtons()
{
    pinMode(BTN_UP, INPUT);
    pinMode(BTN_DOWN, INPUT);
    pinMode(BTN_SELECT, INPUT);

    lastUpReading = digitalRead(BTN_UP);
    lastDownReading = digitalRead(BTN_DOWN);
    lastSelectReading = digitalRead(BTN_SELECT);

    stableUpState = lastUpReading;
    stableDownState = lastDownReading;
    stableSelectState = lastSelectReading;
}

void updateButtons()
{
    unsigned long now = millis();

    upPressed = false;
    downPressed = false;
    selectPressed = false;

    updateButton(BTN_UP, lastUpReading, stableUpState, upPressed, lastUpChange, now);
    updateButton(BTN_DOWN, lastDownReading, stableDownState, downPressed, lastDownChange, now);
    updateButton(BTN_SELECT, lastSelectReading, stableSelectState, selectPressed, lastSelectChange, now);
}

bool buttonUpPressed()
{
    return upPressed;
}

bool buttonDownPressed()
{
    return downPressed;
}

bool buttonSelectPressed()
{
    return selectPressed;
}
