#include <Adafruit_NeoPixel.h>



#define PIN 12
#define Pixels 7

Adafruit_NeoPixel strip = Adafruit_NeoPixel(Pixels, PIN, NEO_GRB + NEO_KHZ800);

int fadeRate = 80;
int MaxBrightness = 90;
int TotalSteps = 100;

void setup() {
#ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  strip.begin();
  for (int i = 0; i < Pixels; i++)
  {
    strip.setPixelColor(i, random(0, MaxBrightness), random(0, MaxBrightness), random(0, MaxBrightness));
  }
  strip.show(); // Initialize all pixels to a Random Color.
}


void loop () {

  uint8_t LED = random(Pixels);  // Pick a random pixel
  // Get the colors of the current pixel.
  uint32_t c = strip.getPixelColor(LED);
  uint8_t  redCur = (c >> 16) & 0xFF;
  uint8_t  greenCur = (c >>  8) & 0xFF;
  uint8_t  blueCur = c & 0xFF;
  //Pick a new random color
  uint8_t redNew = random(0, MaxBrightness);
  uint8_t greenNew = random(0, MaxBrightness);
  uint8_t blueNew = random(0, MaxBrightness);
  // Start fade between the two colors
  for (int i = 1; i < TotalSteps; i++)
  {
    uint8_t red = (((redCur * (TotalSteps - i)) + (redNew * i)) / TotalSteps);
    uint8_t green = (((greenCur * (TotalSteps - i)) + (greenNew * i)) / TotalSteps);
    uint8_t blue = (((blueCur * (TotalSteps - i)) + (blueNew * i)) / TotalSteps);
    // Sets the pixel to the color adjusted in the fade
    strip.setPixelColor(LED, red, green, blue);
    strip.show();
    delay(fadeRate);
  }
  delay(10);
}

