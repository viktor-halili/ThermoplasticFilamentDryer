#ifndef CONTROL_H
#define CONTROL_H

#include <Arduino.h>

void initializeRelay();
void updateControl();
void setRelayState(bool enabled);

#endif
