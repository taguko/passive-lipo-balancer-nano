// passive-lipo-balancer-nano

// OLED
#include "oled.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  // Serial Port
  Serial.begin(9600);

  // pinMode
  pinMode(LED_BUILTIN, OUTPUT);

  // setup
  oled_setup();
}

void loop() {
  oled_handle();
}
