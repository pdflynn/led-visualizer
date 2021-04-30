// Visualizer2.h
// Author: Danny Flynn
// Last Update: 20210430
// Description: Header file containing pin mappings for the Visualizer2 PCB

#define L_CH_0 5
#define L_CH_1 6
#define L_CH_2 7
#define L_CH_3 8
#define L_CH_4 9
#define L_CH_5 10
#define L_CH_6 A0

#define R_CH_0 2
#define R_CH_1 1 // Also TX
#define R_CH_2 0 // Also RX
#define R_CH_3 A5
#define R_CH_4 A4
#define R_CH_5 A3
#define R_CH_6 A2

#define MSG_RST A1
#define MSG_STR 3

#define COLOR_FSM 4
#define NUM_COLOR_MODES 5
#define FADE_DELAY 15

#define L_CH_IN A6
#define R_CH_IN A7

#define DEBOUNCE_DELAY 50

// Color schemes
CRGB colors_1[7] = {CRGB::Red, CRGB(244, 140, 50), CRGB::Yellow, CRGB::Green, CRGB::Blue, CRGB::Indigo, CRGB::Red}; // Rainbow color scheme
CRGB colors_2[7] = {CRGB::Blue, CRGB(0, 51, 204), CRGB(0, 102, 204), CRGB(0, 153, 204), CRGB(0, 204, 255), CRGB(102, 255, 255), CRGB::Blue}; // Ice color scheme
CRGB colors_3[7] = {CRGB(128, 0, 0), CRGB(255, 0, 0), CRGB(255, 102, 0), CRGB(255, 204, 153), CRGB(255, 204, 0), CRGB(255, 255, 255), CRGB(128, 0, 0)}; // Heat color scheme
CRGB colors_4[7] = {CRGB(15, 8, 75), CRGB(255, 229, 212), CRGB(191, 211, 193), CRGB(104, 166, 145), CRGB(105, 79, 93), CRGB(13, 2, 33), CRGB(15, 8, 75)}; // Midnight color scheme
CRGB colors_5[7] = {CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0), CRGB(0, 0, 0)}; // Fade start
