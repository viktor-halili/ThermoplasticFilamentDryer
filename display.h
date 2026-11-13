#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>

void initializeDisplay();

void updateDisplay();

void drawHomeScreen();

void drawMenu();

void drawProfileMenu();

void drawSettingsMenu();

void drawRunning();

void drawAlarm();

void drawComplete();

#endif
