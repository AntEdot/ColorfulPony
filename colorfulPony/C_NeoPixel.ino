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

void xmasAnimation(uint8_t toggle) {
  uint32_t color1, color2;
  uint8_t sizeOfSection = 5;

  if (toggle) {
    color1 = encode32BitColor(255, 0, 0);
    color2 = encode32BitColor(0, 80, 0);
  } else {
    color2 = encode32BitColor(255, 0, 0);
    color1 = encode32BitColor(0, 80, 0);
  }

  int i = 0;
  while (i < NUM_LEDS - NUM_LEDS % (2 * sizeOfSection)) { //Fill all full sections
    setMultiplePixels(i, sizeOfSection, color1);
    setMultiplePixels(i + sizeOfSection, sizeOfSection, color2);
    i += 2 * sizeOfSection;
  }
  setMultiplePixels(i, NUM_LEDS % (2 * sizeOfSection), color1); //Fill the rest
  strip.show();
}

//******BASIC FILL*****************************************************
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
