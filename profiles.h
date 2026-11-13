#ifndef PROFILES_H
#define PROFILES_H

#include <Arduino.h>

//==================================================
//              MATERIAL PROFILE
//==================================================

struct Profile
{
    const char* name;

    float targetTemperature;      // °C
    uint16_t dryingHours;         // hours

    int temperatureServoAngle;    // degrees
    int timerServoAngle;          // degrees
};

//==================================================
//              PROFILE TABLE
//==================================================

const Profile profiles[] =
{
    //  Name   Temp   Hours TempServo TimerServo

    { "PLA",   45.0,     4,      82,        40 },

    { "PETG",  65.0,     6,      220,        38 }
};

//==================================================
//            PROFILE INFORMATION
//==================================================

const uint8_t PROFILE_COUNT = sizeof(profiles) / sizeof(Profile);

#endif