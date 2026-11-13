#include "servos.h"

#include <Servo.h>

#include "config.h"
#include "globals.h"
#include "profiles.h"

static Servo temperatureServo;
static Servo timerServo;

static int limitServoAngle(int angle)
{
    return constrain(angle, SERVO_MIN, SERVO_MAX);
}

static uint8_t getActiveProfileIndex()
{
    if (currentProfile < PROFILE_COUNT)
        return currentProfile;

    return 0;
}

static void moveTemperatureServo(int angle)
{
    temperatureServoPosition = limitServoAngle(angle);
    temperatureServo.write(temperatureServoPosition);
}

static void moveTimerServo(int angle)
{
    timerServoPosition = limitServoAngle(angle);
    timerServo.write(timerServoPosition);
}

void initializeServos()
{
    temperatureServo.attach(TEMP_SERVO_PIN);
    timerServo.attach(TIMER_SERVO_PIN);

    moveServosHome();
}

void moveServosHome()
{
    moveTemperatureServo(TEMP_SERVO_HOME);
    moveTimerServo(TIMER_SERVO_HOME);
}

void applyProfileServos()
{
    uint8_t profileIndex = getActiveProfileIndex();

    moveTemperatureServo(profiles[profileIndex].temperatureServoAngle);
    moveTimerServo(profiles[profileIndex].timerServoAngle);
}
