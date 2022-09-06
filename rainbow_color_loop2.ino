#include <FastLED.h>


const int potPin = A1;    // select the input pin for the potentiometer

#define NUM_LEDS 35     /* The amount of pixels/leds you have */
#define DATA_PIN 6       /* The pin your data line is connected to */
#define LED_TYPE WS2812B /* I assume you have WS2812B leds, if not just change it to whatever you have */
#define SATURATION 205   /* Control the saturation of your leds */

int BRIGHTNESS = 255;   /* Control the brightness of your leds */
int b_read = 80; 

CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<LED_TYPE, DATA_PIN>(leds, NUM_LEDS);
}

void loop() {
  for (int j = 0; j < 255; j++) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CHSV(i - (j * 2), SATURATION, BRIGHTNESS); /* The higher the value 4 the less fade there is and vice versa */ 
    }
    FastLED.show();
    
    b_read = analogRead(potPin);    // read the value from the sensor
    Serial.println(b_read);
    BRIGHTNESS = map(b_read, 20,800,0,255); 
   if (BRIGHTNESS < 10) {  BRIGHTNESS = 0; }
   if (BRIGHTNESS > 255) {  BRIGHTNESS = 255; }
   Serial.println(BRIGHTNESS);  
       Serial.println(" ");

    delay(100); /* Change this to your hearts desire, the lower the value the faster your colors move (and vice versa) */
  }
}
