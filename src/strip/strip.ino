// Randomized LEDs by Jerry Sievert is marked with CC0 1.0. To view a copy of
// this license, visit https://creativecommons.org/publicdomain/zero/1.0/

#include <FastLED.h>

// number of LEDs to control in the strip
#define NUM_LEDS 50

// which data pin that the data line is connected to
#define DATA_PIN D0

// number of steps to do for a color transition, affects "smoothness"
#define STEPS 100

// number of colors to cycle through (defined later)
#define NUM_COLORS 4

// if this is uncommented, makes sure that the color of each LED is always
// changed comment out to disable this behavior
#define NO_REPEAT

// an analog input pin that is free floating for "randomness"
#define RANDOM_PIN A1

// a simple container for colors
struct RGB {
  byte red;
  byte green;
  byte blue;
};

// the LEDs that we address in the strip
CRGB leds[ NUM_LEDS ];

// the colors that we want to cycle between
struct RGB colors[ NUM_COLORS ] = { { .red = 228, .green = 0, .blue = 43 },
                                    { .red = 254, .green = 221, .blue = 0 },
                                    { .red = 0, .green = 199, .blue = 177 },
                                    { .red = 121, .green = 134, .blue = 60 } };

// the start colors for a transition, initialize as black (all 0's)
struct RGB start_colors[ NUM_LEDS ] = { 0 };

// the end colors for each transition
struct RGB end_colors[ NUM_LEDS ];

// takes the current LED number, the start color, the end color, a count of
// steps and the current step sets the LED to the interpolated color between the
// start and end color
void set_color_for_step(int led, struct RGB start, struct RGB end, int count,
                        int current) {
  // the percentage of the way through the color change
  float pct = (float)(count - current) / (float)count;

  // the interpolated value for each color change
  leds[ led ][ 0 ] = ((float)(start.red - end.red) * pct) + end.red;
  leds[ led ][ 1 ] = ((float)(start.green - end.green) * pct) + end.green;
  leds[ led ][ 2 ] = ((float)(start.blue - end.blue) * pct) + end.blue;
}

// set a color to a random copy of the color
void set_random(struct RGB *color) {
  byte which = random(0, NUM_COLORS);

  color->red   = colors[ which ].red;
  color->green = colors[ which ].green;
  color->blue  = colors[ which ].blue;
}

void setup( ) {
  // initialize the LEDs
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

  // set the brightness
  FastLED.setBrightness(255);

  // initialize random
  randomSeed(analogRead(RANDOM_PIN));

  // set up the initial end colors
  for (int i = 0; i < NUM_LEDS; i++) {
    set_random(&end_colors[ i ]);
  }
}

void loop( ) {
  // for each step
  for (int step = 0; step <= STEPS; step++) {
    // and for each step set the led to its transition color
    for (int led = 0; led < NUM_LEDS; led++) {
      set_color_for_step(led, start_colors[ led ], end_colors[ led ], STEPS,
                         step);
    }

    FastLED.show( );

    // a quick delay for each transition
    delay(15);
  }

  // make a copy of the previous state for every led
  for (int led = 0; led < NUM_LEDS; led++) {
    start_colors[ led ].red   = end_colors[ led ].red;
    start_colors[ led ].green = end_colors[ led ].green;
    start_colors[ led ].blue  = end_colors[ led ].blue;

#ifdef NO_REPEAT
    // try to set a new color until the new and old colors don't match
    do {
      set_random(&end_colors[ led ]);
    } while (end_colors[ led ].red == start_colors[ led ].red &&
             end_colors[ led ].green == start_colors[ led ].green &&
             end_colors[ led ].blue == start_colors[ led ].blue);
#else
    // set a new end color
    set_random(&end_colors[ led ]);
#endif
  }

  delay(5000);
}
