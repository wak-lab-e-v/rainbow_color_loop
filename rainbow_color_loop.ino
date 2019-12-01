// Arduino Sketch for NeoPixel / WS2812 LEDs
// cycle a rainbow over all led
//
// based on sketch https://codebender.cc/sketch:57804
//

#include <Adafruit_NeoPixel.h>

const int ledPin = 3;         // set pin number  
const int numLeds = 6;        // the number of the neopixel strip
const int brightness = 80;    // the Brightness of all LEDs
const int cycle_speed = 3000; // time in ms from color to color (0-256)

const int color_shift = 255 / numLeds;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(numLeds, ledPin, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.setBrightness(brightness); 
}

//
// MAIN LOOP
//
void loop() {           
  rainbow(cycle_speed);
  delay(10);
}

// 
// Rainbow Cycle
//
void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {    // color loop
    
    for(i=0; i<strip.numPixels(); i++) {  // led loop   
      strip.setPixelColor(i, Wheel((i*color_shift+j) & 255)); // set 
    }
   
    strip.show();
    delay(wait);
  }
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
//
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } 
  else if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } 
  else {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
