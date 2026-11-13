#include "globals.h"

SystemState currentState = HOME;

uint8_t currentProfile = 0;

float chamberTemperature = 0.0;
float chamberHumidity = 0.0;
bool temperatureSensorValid = false;
unsigned long lastValidTemperatureRead = 0;

float targetTemperature = 0.0;
float temperatureTolerance = DEFAULT_TOLERANCE;

bool relayState = false;

int temperatureServoPosition = 0;
int timerServoPosition = 0;

unsigned long dryingTimeRemaining = 0;
bool timerRunning = false;

int menuIndex = 0;

unsigned long lastButtonPress = 0;
unsigned long lastSensorUpdate = 0;
unsigned long lastDisplayUpdate = 0;
unsigned long lastTimerUpdate = 0;
