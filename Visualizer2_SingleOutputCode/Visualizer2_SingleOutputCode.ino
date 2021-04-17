#include <avr/wdt.h>
#include <FastLED.h>
#include "Visualizer2.h"
#define NUM_LEDS 210
#define LED_SEG 30

CRGB all_leds[NUM_LEDS];

int spectrum[7];
int adj_spectrum[7];


void setup() {

  // Boot up LEDs
  FastLED.addLeds<NEOPIXEL, R_CH_6>(all_leds, NUM_LEDS);
  for (int i = 0; i < NUM_LEDS; i++) {
    all_leds[i] = CRGB(255, 0, 0);
  }
  FastLED.show();
  delay(500); // Pause half a second

  // Set up MSGEQ7
  pinMode(MSG_STR, OUTPUT);
  pinMode(MSG_RST, OUTPUT);
  digitalWrite(MSG_STR, LOW);
  digitalWrite(MSG_RST, LOW);
  delay(1);

  // Reset MSGEQ7
  digitalWrite(MSG_RST, HIGH);
  delay(1);
  digitalWrite(MSG_RST, LOW);
  digitalWrite(MSG_STR, HIGH);
  delay(1);

  Serial.begin(9600);

}

void loop() {
  FastLED.clear();
  readAnalyzer();
  adjustSpectrum();

  for (int i = 0 + (0 * LED_SEG); i < adj_spectrum[0] ; i++) {
    all_leds[i] = CRGB::Red;
  }
  for (int i = (2 * LED_SEG); i > (2 * LED_SEG) - adj_spectrum[1]; i--) {
    all_leds[i] = CRGB(244, 140, 50);
  }
  for (int i = 0 + (2 * LED_SEG); i < adj_spectrum[2] + (2 * LED_SEG); i++) {
    all_leds[i] = CRGB::Yellow;
  }
  for (int i = (4 * LED_SEG); i > (4 * LED_SEG) - adj_spectrum[3]; i--) {
    all_leds[i] = CRGB::Green;
  }
  for (int i = 0 + (4 * LED_SEG); i < adj_spectrum[4] + (4 * LED_SEG); i++) {
    all_leds[i] = CRGB::Blue;
  }
  for (int i = (6 * LED_SEG); i > (6 * LED_SEG) - adj_spectrum[5]; i--) {
    all_leds[i] = CRGB::Indigo;
  }
  for (int i = 0 + (6 * LED_SEG); i < adj_spectrum[0] + (6 * LED_SEG); i++) {
    all_leds[i] = CRGB::Red;
  }
  FastLED.show();
  delay(25);
}

// Reads raw data from MSGEQ7 filters
void readAnalyzer() {
  // Tell MSGEQ7 it is going to be read from
  digitalWrite(MSG_RST, HIGH);
  digitalWrite(MSG_RST, LOW);

  // Read audio channel
  for (int i = 0; i < 7; i++) {
    digitalWrite(MSG_STR, LOW);
    delayMicroseconds(100);
    spectrum[i] = analogRead(L_CH_IN);
    digitalWrite(MSG_STR, HIGH);
    delayMicroseconds(1);
  }
}

// Maps spectrum output to number of LEDs.
void adjustSpectrum() {
  for (int i = 0; i < 7; i++) {
    adj_spectrum[i] = map(spectrum[i], 50, 1023, 1, LED_SEG);
    Serial.print(spectrum[i]);
    Serial.print("  ");
  }
  Serial.println();

}
