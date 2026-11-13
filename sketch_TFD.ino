#include "config.h"
#include "globals.h"

#include "buttons.h"
#include "control.h"
#include "display.h"
#include "menu.h"
#include "sensors.h"
#include "servos.h"
#include "timer.h"

void setup()
{
    initializeDisplay();
    initializeButtons();
    initializeSensors();
    initializeServos();
    initializeRelay();
    initializeTimer();

    drawHomeScreen();
}

void loop()
{
    updateButtons();

    updateSensors();

    updateMenu();

    updateTimer();

    updateControl();

    updateDisplay();
}
