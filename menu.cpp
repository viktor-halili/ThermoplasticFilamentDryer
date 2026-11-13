#include "menu.h"

#include "buttons.h"
#include "config.h"
#include "globals.h"
#include "profiles.h"
#include "servos.h"

const int MAIN_MENU_START = 0;
const int MAIN_MENU_PROFILES = 1;
const int MAIN_MENU_SETTINGS = 2;
const int MAIN_MENU_COUNT = 3;

const float MIN_TEMPERATURE_TOLERANCE = 0.5;
const float MAX_TEMPERATURE_TOLERANCE = 10.0;
const float TEMPERATURE_TOLERANCE_STEP = 0.5;

static void loadCurrentProfile()
{
    if (currentProfile >= PROFILE_COUNT)
        currentProfile = 0;

    targetTemperature = profiles[currentProfile].targetTemperature;
    dryingTimeRemaining = profiles[currentProfile].dryingHours * 3600UL;
}

static void moveMenuIndex(int direction, int itemCount)
{
    menuIndex += direction;

    if (menuIndex < 0)
        menuIndex = itemCount - 1;

    if (menuIndex >= itemCount)
        menuIndex = 0;
}

static void returnHomeAfterTimeout()
{
    if (currentState == MAIN_MENU || currentState == PROFILE_MENU || currentState == SETTINGS_MENU)
    {
        if (millis() - lastButtonPress >= MENU_TIMEOUT)
            currentState = HOME;
    }
}

static void handleHome()
{
    if (buttonSelectPressed())
    {
        menuIndex = MAIN_MENU_START;
        currentState = MAIN_MENU;
    }
}

static void handleMainMenu()
{
    if (buttonUpPressed())
        moveMenuIndex(-1, MAIN_MENU_COUNT);

    if (buttonDownPressed())
        moveMenuIndex(1, MAIN_MENU_COUNT);

    if (!buttonSelectPressed())
        return;

    switch (menuIndex)
    {
        case MAIN_MENU_START:
            loadCurrentProfile();
            applyProfileServos();
            timerRunning = true;
            currentState = RUNNING;
            break;

        case MAIN_MENU_PROFILES:
            menuIndex = currentProfile;
            currentState = PROFILE_MENU;
            break;

        case MAIN_MENU_SETTINGS:
            menuIndex = 0;
            currentState = SETTINGS_MENU;
            break;
    }
}

static void handleProfileMenu()
{
    if (buttonUpPressed())
    {
        if (currentProfile == 0)
            currentProfile = PROFILE_COUNT - 1;
        else
            currentProfile--;
    }

    if (buttonDownPressed())
    {
        currentProfile++;

        if (currentProfile >= PROFILE_COUNT)
            currentProfile = 0;
    }

    menuIndex = currentProfile;
    loadCurrentProfile();

    if (buttonSelectPressed())
    {
        menuIndex = MAIN_MENU_START;
        currentState = MAIN_MENU;
    }
}

static void handleSettingsMenu()
{
    if (buttonUpPressed())
    {
        temperatureTolerance += TEMPERATURE_TOLERANCE_STEP;

        if (temperatureTolerance > MAX_TEMPERATURE_TOLERANCE)
            temperatureTolerance = MAX_TEMPERATURE_TOLERANCE;
    }

    if (buttonDownPressed())
    {
        temperatureTolerance -= TEMPERATURE_TOLERANCE_STEP;

        if (temperatureTolerance < MIN_TEMPERATURE_TOLERANCE)
            temperatureTolerance = MIN_TEMPERATURE_TOLERANCE;
    }

    if (buttonSelectPressed())
    {
        menuIndex = MAIN_MENU_START;
        currentState = MAIN_MENU;
    }
}

static void handleRunning()
{
    if (buttonSelectPressed())
    {
        timerRunning = false;
        moveServosHome();
        currentState = HOME;
    }
}

static void handleComplete()
{
    if (buttonSelectPressed())
    {
        timerRunning = false;
        dryingTimeRemaining = 0;
        moveServosHome();
        currentState = HOME;
    }
}

void updateMenu()
{
    returnHomeAfterTimeout();

    switch (currentState)
    {
        case HOME:
            handleHome();
            break;

        case MAIN_MENU:
            handleMainMenu();
            break;

        case PROFILE_MENU:
            handleProfileMenu();
            break;

        case SETTINGS_MENU:
            handleSettingsMenu();
            break;

        case RUNNING:
            handleRunning();
            break;

        case COMPLETE:
            handleComplete();
            break;

        case ALARM:
            handleComplete();
            break;

        default:
            break;
    }
}
