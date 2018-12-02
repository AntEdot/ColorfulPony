void timeCounter() {
  timeCount++;
  if (timeCount > timeMAX) {
    timeCount = 0;
  }
}

void rainbowCounter() {
  Serial.println(rbCounter);
  rainbow(rbCounter++);
}
