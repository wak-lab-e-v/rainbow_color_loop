// Arduino Sketch for NeoPixel / WS2812 LEDs
// cycle a rainbow over all led
//
// based on sketch https://codebender.cc/sketch:57804
//

#include <Adafruit_NeoPixel.h>
const int potPin = A1;    // select the input pin for the potentiometer
const int ledPin = 6;         // set pin number  
const int numLeds = 35;        // the number of the neopixel strip
const int cycle_speed = 10; // time in ms from color to color (0-256)
const int color_shift = 255 / numLeds;
const int wait = 4+0; // speed 
int brightness = 80;    // the Brightness of all LEDs
int val = 0;       // variable to store the value coming from the sensor

uint16_t i, j;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(numLeds, ledPin, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);  // declare the ledPin as an OUTPUT

  
  strip.begin();


}

//
// MAIN LOOP
//
void loop() {    
         


  // Serial.println(brightness);
  //Serial.print(" ");
  


  
  for(j=0; j<256; j++) {    // color loop
    
    for(i=0; i<strip.numPixels(); i++) {  // led loop   
      strip.setPixelColor(i, Wheel((i*color_shift+j) & 255)); // set 
    }

    brightness = analogRead(potPin);    // read the value from the sensor
    Serial.println(brightness);
    brightness = map(brightness, 20,800,0,255); 
       if (brightness < 10) {  brightness = 0; }
   if (brightness > 255) {  brightness = 255; }
    Serial.println(brightness);
    Serial.println(" ");
    //brightness = val;
    strip.setBrightness(brightness); 
   
    strip.show();
    delay(wait);
  }



  delay(1);
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
