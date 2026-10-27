// OLED Display

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
  display.ssd1306_command(SSD1306_DISPLAYOFF);

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);

  String info;
  display.setCursor(0, 0);
  if (digitalRead(SW1) == HIGH)
    info = "Balance mode";
  else
    info = "Storage mode";
  display.println(info);

  display.setCursor(0, 10);
  info = "V_Cell1:" + String(voltage_cell[0]) + "V";
  display.println(info);
  display.setCursor(0, 20);
  info = "V_Cell2:" + String(voltage_cell[1]) + "V";
  display.println(info);
  display.setCursor(0, 30);
  info = "V_Cell3:" + String(voltage_cell[2]) + "V";
  display.println(info);

  display.display();

  display.ssd1306_command(SSD1306_DISPLAYON);
}
