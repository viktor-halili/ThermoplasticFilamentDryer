#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>

#include "config.h"
#include "profiles.h"

//==================================================
//              SYSTEM STATES
//==================================================

enum SystemState
{
    HOME,
    MAIN_MENU,
    PROFILE_MENU,
    SETTINGS_MENU,
    RUNNING,
    ALARM,
    COMPLETE
};

//==================================================
//            SYSTEM STATE
//==================================================

extern SystemState currentState;

//==================================================
//          CURRENT PROFILE
//==================================================

// Index into profiles[]
extern uint8_t currentProfile;

//==================================================
//        CHAMBER SENSOR VALUES
//==================================================

extern float chamberTemperature;
extern float chamberHumidity;
extern bool temperatureSensorValid;
extern unsigned long lastValidTemperatureRead;

//==================================================
//        CONTROL PARAMETERS
//==================================================

extern float targetTemperature;
extern float temperatureTolerance;

//==================================================
//            RELAY STATUS
//==================================================

extern bool relayState;

//==================================================
//          SERVO POSITIONS
//==================================================

extern int temperatureServoPosition;
extern int timerServoPosition;

//==================================================
//           DRYING TIMER
//==================================================

extern unsigned long dryingTimeRemaining;
extern bool timerRunning;

//==================================================
//              MENU
//==================================================

extern int menuIndex;

extern unsigned long lastButtonPress;

//==================================================
//          NON-BLOCKING TIMERS
//==================================================

extern unsigned long lastSensorUpdate;
extern unsigned long lastDisplayUpdate;
extern unsigned long lastTimerUpdate;

#endif
