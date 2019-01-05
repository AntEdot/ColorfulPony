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

void chaseAnimation(int StartPos) {
  int pos = StartPos;
  uint32_t color = encode32BitColor(0, 0, 255);
  uint8_t len = 70;
  
  pos = chaseObject(pos, color, len);
  yield();
  strip.show();
}


int chaseObject(int pos, uint32_t color, uint8_t len) {
  int per = 100;
  uint8_t decAm = 2;

  for (uint8_t i = 0; i < len; i++) {
    if (pos > NUM_LEDS) {
      pos = 0;
    }
    strip.setPixelColor(pos, colorPercentage(color, per));
    pos++;
    per -= decAm;
    per = charLimitCorrection(per);
  }
  return pos;
}

uint32_t colorPercentage(uint32_t color, float percentage) {

  //Split into r,g,b
  uint8_t r, g, b;
  uint8_t* buf = decode32BitColor(color);
  r = *buf++;
  g = *buf++;
  b = *buf;

  //Set to percantage of base color
  r = (uint8_t)(r * (percentage / 100));
  g = (uint8_t)(g * (percentage / 100));
  b = (uint8_t)(b * (percentage / 100));

  r = charLimitCorrection(r);
  g = charLimitCorrection(g);
  b = charLimitCorrection(b);

  return encode32BitColor(r, g, b);
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
}

void clearStrip () {
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, 0, 0, 0);
  }
  strip.show();
}
