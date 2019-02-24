#include <FastLED.h>
#define NUM_LEDS 300
#define LED_PIN 12
CRGB leds[NUM_LEDS];

int AN_STROBE_PIN = 10; // MSGEQ7 strobe pin
int AN_RESET_PIN = 11; // MSGEQ7 reset pin
int AN_INPUT_PIN = 4; // analog input from MSGEQ7
int LED_SEG = NUM_LEDS / 7;

int spectrum[7]; // holds frequency band audio data
int adjusted[7];

void setup() {
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0, 0, 255);
  }
  FastLED.show();

  
  Serial.begin(9600);
  pinMode(AN_STROBE_PIN, OUTPUT);
  pinMode(AN_RESET_PIN, OUTPUT);

  // MSGEQ7 Initial Conditions
  digitalWrite(AN_RESET_PIN, LOW);
  digitalWrite(AN_STROBE_PIN, LOW);
  delay(1);

  // Reset MSGEQ7
  digitalWrite(AN_RESET_PIN, HIGH);
  delay(1);
  digitalWrite(AN_RESET_PIN, LOW);
  digitalWrite(AN_STROBE_PIN, HIGH);
  delay(1);

}

void loop() {
  FastLED.clear();
  readAnalyzer();
  for (int i = 0; i < 7; i++) {
    adjusted[i] = map(spectrum[i], 400, 850, 1, LED_SEG);
    Serial.print(spectrum[i]);
    Serial.print("__");
  }
  Serial.println();

  for (int i = 0 + (0 * LED_SEG); i < adjusted[0] ; i++) {
    leds[i] = CRGB::Red;
  }
  for (int i = 0 + (1 * LED_SEG); i < adjusted[1] + (1 * LED_SEG); i++) {
    leds[i] = CRGB(244, 140, 50);
  }
  for (int i = 0 + (2 * LED_SEG); i < adjusted[2] + (2 * LED_SEG); i++) {
    leds[i] = CRGB::Yellow;
  }
  for (int i = 0 + (3 * LED_SEG); i < adjusted[3] + (3 * LED_SEG); i++) {
    leds[i] = CRGB::Green;
  }
  for (int i = 0 + (4 * LED_SEG); i < adjusted[4] + (4 * LED_SEG); i++) {
    leds[i] = CRGB::Blue;
  }
  for (int i = 0 + (5 * LED_SEG); i < adjusted[5] + (5 * LED_SEG); i++) {
    leds[i] = CRGB::Indigo;
  }
  for (int i = 0 + (6 * LED_SEG); i < adjusted[0] + (6 * LED_SEG); i++) {
    leds[i] = CRGB::Red;
  }
  FastLED.show();

}

void readAnalyzer() {
  // tell the analyzer we're going to read the audio bands
  digitalWrite(AN_RESET_PIN, HIGH);
  digitalWrite(AN_RESET_PIN, LOW);

  // read a single audio channel
  for (int i = 0; i < 7; i++) {
    digitalWrite(AN_STROBE_PIN, LOW);
    delayMicroseconds(100);
    spectrum[i] = analogRead(AN_INPUT_PIN);
    digitalWrite(AN_STROBE_PIN, HIGH);
    delayMicroseconds(1);
  }
  
}
