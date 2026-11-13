#include "sensors.h"

#include <DHT.h>

#include "config.h"
#include "globals.h"

DHT dht(DHT_PIN, DHTTYPE);

void initializeSensors()
{
    dht.begin();
}

void updateSensors()
{
    if (millis() - lastSensorUpdate < SENSOR_UPDATE_INTERVAL)
        return;

    lastSensorUpdate = millis();

    float temp = dht.readTemperature();
    float hum = dht.readHumidity();

    if (!isnan(temp))
    {
        chamberTemperature = temp;
        temperatureSensorValid = true;
        lastValidTemperatureRead = lastSensorUpdate;
    }

    if (!isnan(hum))
        chamberHumidity = hum;
}

float getTemperature()
{
    return chamberTemperature;
}

float getHumidity()
{
    return chamberHumidity;
}

bool temperatureReadingIsFresh()
{
    if (!temperatureSensorValid)
        return false;

    return millis() - lastValidTemperatureRead <= SENSOR_STALE_TIMEOUT;
}
