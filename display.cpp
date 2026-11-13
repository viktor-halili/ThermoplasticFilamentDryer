#include "display.h"

#include <string.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "config.h"
#include "globals.h"
#include "profiles.h"
#include "sensors.h"

static SystemState previousState = HOME;
static char displayedLines[LCD_ROWS][LCD_COLUMNS + 1] = {{ '\0' }};

LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);

static uint8_t getActiveProfileIndex()
{
    if (currentProfile < PROFILE_COUNT)
        return currentProfile;

    return 0;
}

static float getActiveTargetTemperature()
{
    if (targetTemperature > 0.0)
        return targetTemperature;

    return profiles[getActiveProfileIndex()].targetTemperature;
}

static void resetDisplayCache()
{
    for (uint8_t row = 0; row < LCD_ROWS; row++)
        displayedLines[row][0] = '\0';
}

static void writeLine(uint8_t row, const char* text)
{
    if (row >= LCD_ROWS)
        return;

    char padded[LCD_COLUMNS + 1];

    for (uint8_t column = 0; column < LCD_COLUMNS; column++)
        padded[column] = ' ';

    padded[LCD_COLUMNS] = '\0';

    for (uint8_t column = 0; column < LCD_COLUMNS && text[column] != '\0'; column++)
        padded[column] = text[column];

    if (strncmp(displayedLines[row], padded, LCD_COLUMNS) == 0)
        return;

    lcd.setCursor(0, row);
    lcd.print(padded);
    strncpy(displayedLines[row], padded, LCD_COLUMNS + 1);
}

static void formatTemperature(char* buffer, size_t bufferSize)
{
    if (!temperatureReadingIsFresh())
    {
        snprintf(buffer, bufferSize, "--.-C");
        return;
    }

    char value[8];
    dtostrf(chamberTemperature, 0, 1, value);
    snprintf(buffer, bufferSize, "%sC", value);
}

static void formatHumidity(char* buffer, size_t bufferSize)
{
    char value[8];
    dtostrf(chamberHumidity, 0, 0, value);
    snprintf(buffer, bufferSize, "%s%%", value);
}

static void formatTimeRemaining(char* buffer, size_t bufferSize)
{
    unsigned long totalSeconds = dryingTimeRemaining;
    unsigned int hours = totalSeconds / 3600;
    unsigned int minutes = (totalSeconds % 3600) / 60;

    snprintf(buffer, bufferSize, "%02u:%02u", hours, minutes);
}

void initializeDisplay()
{
    lcd.init();
    lcd.backlight();
    lcd.clear();
    resetDisplayCache();
}

void updateDisplay()
{
    unsigned long now = millis();
    bool stateChanged = currentState != previousState;

    if (!stateChanged && (now - lastDisplayUpdate) < DISPLAY_REFRESH_INTERVAL)
        return;

    lastDisplayUpdate = now;

    if (stateChanged)
    {
        resetDisplayCache();
        previousState = currentState;
    }

    switch (currentState)
    {
        case HOME:
            drawHomeScreen();
            break;

        case MAIN_MENU:
            drawMenu();
            break;

        case PROFILE_MENU:
            drawProfileMenu();
            break;

        case SETTINGS_MENU:
            drawSettingsMenu();
            break;

        case RUNNING:
            drawRunning();
            break;

        case ALARM:
            drawAlarm();
            break;

        case COMPLETE:
            drawComplete();
            break;

        default:
            drawHomeScreen();
            break;
    }
}

void drawHomeScreen()
{
    uint8_t profileIndex = getActiveProfileIndex();
    char target[8];
    char temperature[8];
    char humidity[8];
    char line[LCD_COLUMNS + 1];

    dtostrf(getActiveTargetTemperature(), 0, 0, target);
    formatTemperature(temperature, sizeof(temperature));
    formatHumidity(humidity, sizeof(humidity));

    snprintf(line, sizeof(line), "TFD %s %sC", profiles[profileIndex].name, target);
    writeLine(0, line);

    snprintf(line, sizeof(line), "%s %s Sel", temperature, humidity);
    writeLine(1, line);
}

void drawMenu()
{
    const char* menuItems[] =
    {
        "Start Drying",
        "Profiles",
        "Settings"
    };

    const uint8_t menuCount = sizeof(menuItems) / sizeof(menuItems[0]);
    uint8_t safeIndex = menuIndex;
    char line[LCD_COLUMNS + 1];

    if (safeIndex >= menuCount)
        safeIndex = 0;

    writeLine(0, "Main Menu");

    snprintf(line, sizeof(line), ">%s", menuItems[safeIndex]);
    writeLine(1, line);
}

void drawProfileMenu()
{
    uint8_t profileIndex = getActiveProfileIndex();
    char target[8];
    char line[LCD_COLUMNS + 1];

    dtostrf(profiles[profileIndex].targetTemperature, 0, 0, target);

    snprintf(line, sizeof(line), "Profile %u/%u", profileIndex + 1, PROFILE_COUNT);
    writeLine(0, line);

    snprintf(line, sizeof(line), "%s %sC %uh",
             profiles[profileIndex].name,
             target,
             profiles[profileIndex].dryingHours);
    writeLine(1, line);
}

void drawSettingsMenu()
{
    char tolerance[8];
    char line[LCD_COLUMNS + 1];

    dtostrf(temperatureTolerance, 0, 1, tolerance);

    writeLine(0, "Settings");

    snprintf(line, sizeof(line), "Tol %sC R:%s", tolerance, relayState ? "ON" : "OFF");
    writeLine(1, line);
}

void drawRunning()
{
    char target[8];
    char temperature[8];
    char humidity[8];
    char remaining[8];
    char line[LCD_COLUMNS + 1];

    dtostrf(getActiveTargetTemperature(), 0, 0, target);
    formatTemperature(temperature, sizeof(temperature));
    formatHumidity(humidity, sizeof(humidity));
    formatTimeRemaining(remaining, sizeof(remaining));

    snprintf(line, sizeof(line), "T %s/%sC %s",
             temperature,
             target,
             relayState ? "ON" : "OFF");
    writeLine(0, line);

    snprintf(line, sizeof(line), "H %s %s", humidity, remaining);
    writeLine(1, line);
}

void drawAlarm()
{
    char line[LCD_COLUMNS + 1];

    writeLine(0, "ALARM");

    if (!temperatureReadingIsFresh())
    {
        writeLine(1, "Sensor fault");
        return;
    }

    char temperature[8];
    formatTemperature(temperature, sizeof(temperature));
    snprintf(line, sizeof(line), "Temp %s", temperature);
    writeLine(1, line);
}

void drawComplete()
{
    writeLine(0, "Drying Complete");
    writeLine(1, "Select to reset");
}
