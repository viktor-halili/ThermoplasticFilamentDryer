#include "timer.h"

#include "config.h"
#include "globals.h"

void initializeTimer()
{
    lastTimerUpdate = millis();
}

void updateTimer()
{
    if (!timerRunning)
    {
        lastTimerUpdate = millis();
        return;
    }

    if (dryingTimeRemaining == 0)
    {
        timerRunning = false;
        currentState = COMPLETE;
        return;
    }

    unsigned long now = millis();
    unsigned long elapsed = now - lastTimerUpdate;

    if (elapsed < TIMER_UPDATE_INTERVAL)
        return;

    unsigned long elapsedSeconds = elapsed / 1000UL;

    if (elapsedSeconds == 0)
        elapsedSeconds = 1;

    if (elapsedSeconds >= dryingTimeRemaining)
    {
        dryingTimeRemaining = 0;
        timerRunning = false;
        currentState = COMPLETE;
        lastTimerUpdate = now;
        return;
    }

    dryingTimeRemaining -= elapsedSeconds;
    lastTimerUpdate += elapsedSeconds * 1000UL;
}
