// 

void oled_setup() {
  // Wait for display
  delay(500);
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true) {};  // Don't proceed, loop forever
  }
  // Clear the buffer
  display.clearDisplay();
  display.display();
}

void oled_handle() {
}
