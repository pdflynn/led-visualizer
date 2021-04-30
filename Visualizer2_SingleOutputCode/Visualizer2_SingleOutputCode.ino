#include <avr/wdt.h>
#include <FastLED.h>
#include "Visualizer2.h"
#define NUM_LEDS 210
#define LED_SEG 30

// LED strip
CRGB all_leds[NUM_LEDS];
CRGB channel_colors[7];

// MSGEQ7 spectrum and adjusted spectrum
int spectrum[7];
int adj_spectrum[7];

// For button FSM
int colorBtnState;
int lastColorBtnState = 0;
unsigned long lastColorDebounceTime = 0;
int colorMode = 0;

// For fading colors
int tLastRefresh = 0;
int rFade = 255;
int gFade = 0;
int bFade = 0;

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

  // Set up color FSM 
  pinMode(COLOR_FSM, INPUT);
  assignArray(colors_1);

  Serial.begin(9600);

}

void loop() {
  FastLED.clear();
  readAnalyzer(); // Get MSGEQ7 Values
  adjustSpectrum(); // Map MSGEQ7 values to number of LEDs
  updateColorBtn(); // Sense if color button has been pressed
  updateColors(); // Update colors to account for changing color schemes
  updateFade(); // Update fade color scheme values


  for (int i = 0 + (0 * LED_SEG); i < adj_spectrum[0] ; i++) {
    all_leds[i] = channel_colors[0];
  }
  for (int i = (2 * LED_SEG); i > (2 * LED_SEG) - adj_spectrum[1]; i--) {
    all_leds[i] = channel_colors[1];
  }
  for (int i = 0 + (2 * LED_SEG); i < adj_spectrum[2] + (2 * LED_SEG); i++) {
    all_leds[i] = channel_colors[2];
  }
  for (int i = (4 * LED_SEG); i > (4 * LED_SEG) - adj_spectrum[3]; i--) {
    all_leds[i] = channel_colors[3];
  }
  for (int i = 0 + (4 * LED_SEG); i < adj_spectrum[4] + (4 * LED_SEG); i++) {
    all_leds[i] = channel_colors[4];
  }
  for (int i = (6 * LED_SEG); i > (6 * LED_SEG) - adj_spectrum[5]; i--) {
    all_leds[i] = channel_colors[5];
  }
  for (int i = 0 + (6 * LED_SEG); i < adj_spectrum[0] + (6 * LED_SEG); i++) {
    all_leds[i] = channel_colors[6];
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
//    Serial.print(spectrum[i]);
//    Serial.print("  ");
  }
//  Serial.println();

}

// Updates the "button pressed" variable (debounce FSM)
void updateColorBtn() {
  int reading = digitalRead(COLOR_FSM);
  Serial.println(reading);
  if (reading != lastColorBtnState) {
    lastColorDebounceTime = millis();
  }

  Serial.println(millis() - lastColorDebounceTime);
  if ((millis() - lastColorDebounceTime) > DEBOUNCE_DELAY) {
    Serial.println("TRUE");
    if (reading != colorBtnState) {
      colorBtnState = reading;

      if (colorBtnState == 1) {
        circIncColorMode();
        updateColors();
        Serial.println("BTN PRESSED");
      }
    }
  }
  lastColorBtnState = reading;

}

// Updates the color mode state
void updateColors() {
  switch(colorMode) {
    case 0: // RAINBOW
      assignArray(colors_1);
      break;
    case 1: // ICE
      assignArray(colors_2);
      break;
    break;
    case 2: // HEAT
      assignArray(colors_3);
      break;
    break;
    case 3: // MIDNIGHT
      assignArray(colors_4);
      break;
    break;
    case 4: // FADE
      assignArray(colors_5);
    break;

  }
}

// Copies color array
void assignArray(CRGB arr[7]) {
  for (int i = 0; i < 7; i++) {
    channel_colors[i] = arr[i];
  }
}

// Circular increment the color state
void circIncColorMode() {
  colorMode = (colorMode + 1) % NUM_COLOR_MODES;
}

// Circular increment for fading color schemes
void updateFade() {
  if (millis() - tLastRefresh > FADE_DELAY) {
    if (rFade > 0 && bFade == 0) {
      rFade--;
      gFade++;
    }
    if (gFade > 0 && rFade == 0) {
      gFade--;
      bFade++;
    }
    if (bFade > 0 && gFade == 0) {
      rFade++;
      bFade--;
    }
    tLastRefresh = millis();
  }
  for (int i = 0; i < 7; i++) {
    colors_5[i] = CRGB(rFade, gFade, bFade);
  }
}
