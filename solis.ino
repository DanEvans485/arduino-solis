#include <FastLED.h>
#include <Vector.h>

using namespace std;

#define PIN       23
#define NUMPIXELS 137

CRGB leds[NUMPIXELS];

void setup() {
  FastLED.addLeds<WS2812B, PIN, GRB>(leds, NUMPIXELS).setCorrection(TypicalLEDStrip);
  
  Serial.begin(115200);
}

int HALFNUMPIXELS = round(NUMPIXELS / 2);

float timeyWimey = 0;
int center = 60;


class GradientPoint {
  public:
    float position;
    CRGB color;

  public:
    GradientPoint(
      CRGB color,
      float position
    ) {
      this->color = color;
      this->position = position; 
    }
};

class Gradient {
  protected:
    Vector<GradientPoint> points;

  public:
    Gradient() {
      
    }

    void add(GradientPoint point) {
      this->points.push_back(point);
    }
};


float falloff = 8;
//float fDistance = 1 / (2 * falloff);
//float nightMin  = 0.25 - fDistance;
//float nightMax  = 0.75 + fDistance;
//float dayMin    = 0.25 + fDistance;
//float dayMax    = 0.75 - fDistance;

float sunRange = 0;

float dawnSize = 0.1;
float sunRiseBrightness = 0.2;

void loop() {
  timeyWimey = 0.25;
//  timeyWimey += 0.001;
//
//  if (timeyWimey > 0.5) {
//    timeyWimey -= 1 - 0.5;
//  }

  float extraTimey = 0.5f - fabs(timeyWimey - 0.5f);
  float closest = min(
    1.0,
    max(
      0.0,
      (extraTimey - 0.25 + dawnSize) / dawnSize
    )
  );
  float furthest = min(
    1.0,
    max(
      0.0,
      (extraTimey - 0.25) / dawnSize
    )
  );

  Serial.println((String) timeyWimey + " | " + (String) closest);

  for(int i = 0; i < NUMPIXELS; i++) {  
    leds[i] = CRGB(0, 0, 0);
  }

  for(int i = 0; i <= HALFNUMPIXELS; i++) {
    float nIndex = fabs((float) i / (float) HALFNUMPIXELS);

    float brightness = furthest - ((furthest - closest) * pow(1 - nIndex, falloff));

    float r = 1; //min(1.0f, max(0.0f, 1 / (0.1 * nIndex + 1)));
    float g = 1; //min(1.0f, max(0.0f, (1 / (40 * nIndex + 1)) * (1 - nIndex)));
    float b = 1; // min(1.0f, max(0.0f, 1 / (1 * (1 - nIndex) + 1)));

    CRGB pixelColor = CRGB(
      r * 60 * brightness,
      g * 60 * brightness,
      b * 60 * brightness
    );

    int led = (center - i) % NUMPIXELS;
    led = led < 0 ? led + NUMPIXELS : led;
    leds[led] = pixelColor;

    led = (center + i) % NUMPIXELS;
    led = led < 0 ? led + NUMPIXELS : led;
    leds[led] = pixelColor;
  }

  leds[center] = CRGB(255,0,0);

  FastLED.show();
  delay(10);
}
