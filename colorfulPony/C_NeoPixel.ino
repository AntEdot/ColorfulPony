void waveAnimation (uint8_t red, uint8_t green, uint8_t blue) {
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, red, green, blue);
    strip.show();
    delay(2);
  }
}

void setStripToPrev() {
  printEEPROM();
  EEPROM.get(0, memory);
  fillStrip(memory.color.R, memory.color.G, memory.color.B);
  strip.setBrightness(memory.brightness);
}

void fillStrip () {
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, 255, 255, 255);
  }
  strip.show();
}

void fillStrip (uint32_t color) {
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, color);
  }
  strip.show();
}

void fillStrip (uint8_t red, uint8_t green, uint8_t blue) {
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, red, green, blue);
  }
  strip.show();

  storeInStruct(red, green, blue);
  putInEEPROM();

  Serial.println();
  Serial.print("Color charged to: ");
  Serial.print(red, DEC);
  Serial.print(" ");
  Serial.print(green, DEC);
  Serial.print(" ");
  Serial.print(blue, DEC);
  Serial.println();
}

void clearStrip () {
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, 0, 0, 0);
  }
  strip.show();
}
