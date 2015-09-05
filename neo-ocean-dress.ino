#include <Adafruit_NeoPixel.h>

const int NUM_LEDS_STRIPS = 10;
const int NUM_LEDS_STRIP_BELT = 23;
const int PIN_1 = 11;
const int PIN_2 = 2;
const int PIN_3 = 9;

Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(NUM_LEDS_STRIPS, PIN_1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(NUM_LEDS_STRIPS, PIN_2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(NUM_LEDS_STRIP_BELT, PIN_3, NEO_GRB + NEO_KHZ800);

void setup() {
  delay( 3000 ); // power-up safety delay TODO: check if useful

  strip1.begin();
  strip1.show(); // Initialize all pixels to 'off'

  strip2.begin();
  strip2.show(); // Initialize all pixels to 'off'

  strip3.begin();
  strip3.show(); // Initialize all pixels to 'off'
}

void loop() {
  const int start_color1 = 100;
  const int end_color1 = 170;

  const int start_color2 = 44;
  const int end_color2 = 88;
  
  partial_rainbow(strip1, start_color1, end_color1);
  partial_rainbow(strip2, start_color2, end_color2);
  partial_rainbow(strip3, start_color2, end_color2);
  
  delay(300);
}

void partial_rainbow(Adafruit_NeoPixel& strip, int start_color, int end_color) {
  
  for(int j=start_color; j<end_color; j++) {
    for(int i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(strip, (i+j) & 255));
    }
    strip.show();
    delay(30);
  }
  
  for(int j=end_color; j>start_color; j--) {
    for(int i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(strip, (i+j) & 255));
    }
    strip.show();
    delay(30);
  }
  
}

uint32_t Wheel(Adafruit_NeoPixel& strip, byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

