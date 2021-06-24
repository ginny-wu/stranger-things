#include <FastLED.h>
// Number of LEDs on your light string
#define NUM_LEDS 50
// Which data pin on the Arduino is hooked up to the Data In wire on your light string
#define DATA_PIN 6
// For some reason, red and green were flipped on my lights. You might want to test these.
#define GREEN CRGB::Red
#define RED CRGB::Green
#define BLUE CRGB::Blue
#define BLACK CRGB::Black
#define WHITE CRGB::White
#define MAX_BRIGHTNESS 255

// This is the word that will be blinking, no spaces or special characters
char BLINK_WORD [] = "LETSGODODGERS";

long randNumber;
// Pick a random color from this array
CRGB colors [4] = {RED, GREEN, BLUE, WHITE };
CRGB color;
CRGB leds[NUM_LEDS];

// Map characters to LED numbers, starting with index 0. 
// index 0 == 'A', 1 == 'B', etc
// Change these to match how your lights are actually hung
int characters [26] = {
  39, // A 
  41, // B
  42, // C
  43, // D
  45, // E
  46, // F
  47, // G
  48, // H
  34, // I
  32, // J
  31, // K
  30, // L
  29, // M
  27, // N
  26, // O
  25, // P
  23, // Q
  6, // R
  8, // S
  9, // T
  11, // U
  12, // V
  13, // W
  15, // X
  16, // Y
  17, // Z
};

// Map a lower case char to an LED
int charToLED(char c) {
  int i;
  if (c >= 97 && c <= 122) {
    // Lowercase
    i = c - 97;
  } else {
    // Uppercase
    i = c - 65;
  }

  return characters[i];
}

void initFlash() {
  // Flash every light as white 
  for ( int i = 0; i < NUM_LEDS; i = i + 1 ) {
    leds[i] = WHITE;
  }
  
  // Slowly go from off to full brightness
  for ( int j = 0; j < MAX_BRIGHTNESS; j = j + 1) {
    FastLED.setBrightness(j);
    delay(10);
    FastLED.show();
  }
  
  // Go from full brightness to off
  for ( int j = MAX_BRIGHTNESS; j >= 0; j = j - 1) {
    FastLED.setBrightness(j);
    delay(10);
    FastLED.show();
  }
  
  // Make the colored flashes full brightness
  FastLED.setBrightness(MAX_BRIGHTNESS);
  
  // Reset the LEDs to black so we can blink the word
  for ( int i = 0; i < NUM_LEDS; i = i + 1 ) {
    leds[i] = BLACK;
  }
  delay(3000);
}

// Flash a random color for each character
void blinkMessage() {
  int x, c;
  for ( int i = 0; i < sizeof(BLINK_WORD); i = i + 1 ) {
    color = colors[random(4)];
    c = BLINK_WORD[i];
    x = charToLED(c);
    leds[x] = color; FastLED.show(); delay(1000);
    leds[x] = BLACK; FastLED.show(); delay(800);
  }
  delay(2000);
}

// Run when the Arduino boots up. Set up FastLED
void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  randomSeed(analogRead(0));
}

// Run in a loop continuously
void loop() {
  initFlash();
  blinkMessage();
}

