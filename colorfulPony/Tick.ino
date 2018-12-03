void timeCounter() {
  setStripToPrev();
}

void rainbowAmimation() {
  Serial.println(rbCounter);
  rainbow(rbCounter++);
}

void xmasToggle() {
  static uint8_t xmasToggle = 0;
  xmasToggle = toggle(xmasToggle);
  xmasAnimation(xmasToggle);
}

uint8_t toggle(uint8_t tog) {
  if (tog) {
    tog = 0;
  } else {
    tog = 1;
  }
  return tog;
}
