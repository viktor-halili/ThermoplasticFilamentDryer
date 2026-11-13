#include "control.h"

#include "config.h"
#include "globals.h"
#include "sensors.h"

void setRelayState(bool enabled)
{
    relayState = enabled;
    digitalWrite(RELAY_PIN, relayState ? RELAY_ON : RELAY_OFF);
}

void initializeRelay()
{
    pinMode(RELAY_PIN, OUTPUT);
    setRelayState(false);
}

void updateControl()
{
    if (currentState != RUNNING || !timerRunning)
    {
        setRelayState(false);
        return;
    }

    if (!temperatureReadingIsFresh() || targetTemperature <= 0.0)
    {
        setRelayState(false);
        currentState = ALARM;
        return;
    }

    if (chamberTemperature >= MAX_SAFE_TEMPERATURE)
    {
        setRelayState(false);
        currentState = ALARM;
        return;
    }

    if (!relayState && chamberTemperature <= targetTemperature - temperatureTolerance)
        setRelayState(true);

    if (relayState && chamberTemperature >= targetTemperature + temperatureTolerance)
        setRelayState(false);
}
