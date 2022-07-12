// lights.h - Handling of LEDS
//
// Adapted from code provided by the FastLED library by Alison N. Norman

#ifndef INCLUDED_LIGHTS
#define INCLUDED_LIGHTS
#define POTENTIOMETER_PIN A0


#include "FastLED.h"

#define LED_PIN     7
#define NUM_LEDS    25
#define MAX_BRIGHTNESS 255
#define BRIGHTNESS  255   //MAX is 255.  Colors may be more vibrant at lower brightness values
#define LED_TYPE    WS2811

#define UPDATES_PER_SECOND 100

extern CRGB leds[NUM_LEDS+1];

void leds_init();


#endif // INCLUDED_LIGHTS
