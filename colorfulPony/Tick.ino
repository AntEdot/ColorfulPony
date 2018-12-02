void timeCounter() {
 setStripToPrev();
}

void rainbowCounter() {
  Serial.println(rbCounter);
  rainbow(rbCounter++);
}

