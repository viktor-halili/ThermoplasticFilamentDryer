#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>

void initializeSensors();

void updateSensors();

float getTemperature();

float getHumidity();

bool temperatureReadingIsFresh();

#endif
