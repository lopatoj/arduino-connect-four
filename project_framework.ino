#include "FastLED.h"
#include "lights.h"
#include "project.h"

#define POTENTIOMETER_PIN A0

CRGB leds[NUM_LEDS+1];

void setup()
{
  delay( 3000 ); // power-up safety delay
  Serial.begin(9600); //enables serial output for debugging
  
  //WS2811 on pin 7, color sequence, lights data structure, and number of lights for controller
  FastLED.addLeds<LED_TYPE, LED_PIN, RGB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );

  FastLED.setBrightness(  BRIGHTNESS );  //sets the brightness for the strand of LEDs.  Default is 64, max is 255.
 
  leds_init(); 
}

void loop()
{ 
  FastLED.setBrightness(  BRIGHTNESS );
  int i = 0;
  while(true) {
    i++;
    int player = i%2+1;
    //Serial.println(player);
    select(player);
    logic(player);
    disp();
    if(ifWinner(player)){
      break;
    }
    if(tied()) {
      break;
    }
  }
  winningAnimation();
}
