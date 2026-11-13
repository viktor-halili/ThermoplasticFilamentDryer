#ifndef BUTTONS_H
#define BUTTONS_H

#include <Arduino.h>

void initializeButtons();
void updateButtons();

bool buttonUpPressed();
bool buttonDownPressed();
bool buttonSelectPressed();

#endif