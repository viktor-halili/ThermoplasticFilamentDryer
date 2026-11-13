#ifndef CONFIG_H
#define CONFIG_H

//==================================================
//                  LIBRARIES
//==================================================

#include <Arduino.h>

//==================================================
//                  PIN ASSIGNMENTS
//==================================================

// Sensors
const uint8_t DHT_PIN = 2;

// Relay
const uint8_t RELAY_PIN = 3;

// Buttons
const uint8_t BTN_UP     = 4;
const uint8_t BTN_DOWN   = 5;
const uint8_t BTN_SELECT = 6;

// Ignore repeated button changes inside this window to filter switch bounce.
const unsigned long BUTTON_DEBOUNCE_INTERVAL = 50;

// Buttons use external pull-down resistors: unpressed LOW, pressed HIGH.
const bool BUTTON_PRESSED = HIGH;
const bool BUTTON_RELEASED = LOW;

// Servos
const uint8_t TEMP_SERVO_PIN  = 9;
const uint8_t TIMER_SERVO_PIN = 10;

//==================================================
//                  LCD
//==================================================

const uint8_t LCD_ADDRESS = 0x27;
const uint8_t LCD_COLUMNS = 16;
const uint8_t LCD_ROWS    = 2;

//==================================================
//                  DHT22
//==================================================

#define DHTTYPE DHT22

const unsigned long SENSOR_UPDATE_INTERVAL = 2000;
const unsigned long SENSOR_STALE_TIMEOUT = 10000;

//==================================================
//              DISPLAY TIMING
//==================================================

const unsigned long DISPLAY_REFRESH_INTERVAL = 250;
const unsigned long MENU_TIMEOUT = 15000;

//==================================================
//                  TIMER
//==================================================

const unsigned long TIMER_UPDATE_INTERVAL = 1000;

//==================================================
//             TEMPERATURE CONTROL
//==================================================

const float DEFAULT_TOLERANCE = 2.0;
const float MAX_SAFE_TEMPERATURE = 80.0;

//==================================================
//              RELAY LOGIC
//==================================================

// Change these if your relay is active LOW
const bool RELAY_ON  = HIGH;
const bool RELAY_OFF = LOW;

//==================================================
//             SERVO LIMITS
//==================================================

const int SERVO_MIN = 0;
const int SERVO_MAX = 180;

//==================================================
//      DEFAULT STARTUP POSITIONS
//==================================================

const int TEMP_SERVO_HOME  = 0;
const int TIMER_SERVO_HOME = 0;

#endif
