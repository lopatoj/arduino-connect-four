// lights.cpp - Lights buffer handling
//
// Adapted from code by John Graham-Cumming by Alison N. Norman
//

#include "lights.h"
#define POTENTIOMETER_PIN A0

// leds_init: Initializes leds to all pixels off and mirrors
// that to the actual display
void leds_init()
{
  for ( int x = 0; x < NUM_LEDS + 1; ++x )
    leds[x] = CRGB::Black;

  FastLED.show();
}
