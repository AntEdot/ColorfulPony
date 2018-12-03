void printTest() {
  ticker.detach();
  Serial.println();
  Serial.println("Homey print test succesful!");
  Serial.print("Value: ");
  Serial.println(Homey.value);
  Serial.println("Done");
}

void setNeoPixelBrightness() {
  ticker.detach();
  int brightValue = Homey.value.toInt();
  brightValue = charLimitCorrection(brightValue);

  strip.setBrightness(brightValue);
  strip.show();

  Serial.println();
  Serial.print("Brightness charged to: ");
  Serial.println(brightValue, DEC);
}

void setNeoPixelColor() {
  ticker.detach();
  int color = Homey.value.toInt();
  uint8_t red, green, blue = 0;

  blue = charLimitCorrection(color % 1000);
  color = color / 1000;
  green = charLimitCorrection(color % 1000);
  color = color / 1000;
  red = charLimitCorrection(color % 1000);
  color = color / 1000;

  fillStrip(red, green, blue);
}

void doWaveAnimation () {
  ticker.detach();
  int color = Homey.value.toInt();
  uint8_t red, green, blue = 0;

  blue = charLimitCorrection(color % 1000);
  color = color / 1000;
  green = charLimitCorrection(color % 1000);
  color = color / 1000;
  red = charLimitCorrection(color % 1000);
  color = color / 1000;

  waveAnimation(red, green, blue);
}

void setStripBrightness () {
  float brightValue = Homey.value.toFloat();
  brightValue = brightValue * 100;                                //move value past the decimal point to be albe to convert to int.
  uint8_t stripBrightValue = map(brightValue, 0, 100, 1, 255);

  strip.setBrightness(brightValue);
  strip.show();

  storeInStruct(brightValue);
  putInEEPROM();
}

void setStripColor () {
  String str = Homey.value;
  
  if (str.equals(prevInputStr)) {
    return;
  }
  
  Serial.println(str);
  ticker.detach();
  
  uint8_t boundryOne = str.indexOf('|');
  uint8_t boundryTwo = str.indexOf('|', boundryOne + 1);
  uint8_t boundryThr = str.indexOf('|', boundryTwo + 1);

  String colorORtemp = str.substring(0, boundryOne);
  float temF = (str.substring(boundryOne + 1, boundryTwo)).toFloat();
  float hueF = (str.substring(boundryTwo + 1, boundryThr)).toFloat();    //Pick out substring convert to float and multiply by 100 to convert to int
  float satF = (str.substring(boundryThr + 1)).toFloat();

  temF = temF * 100;
  hueF = hueF * 100;
  satF = satF * 100;

  int      tem = map(temF, 0, 100, 10000, 2000);
  uint16_t hue = map(hueF, 0, 100, 0, 359);
  uint8_t  sat = map(satF, 0, 100, 0, 100);
  Serial.println(tem);
  Serial.println(hue);
  Serial.println(sat);

  prevInputStr = str;

  colorORtemp.trim(); //remove whitespace

  if ((colorORtemp.equals("temperaturetemperature")) or (colorORtemp.equals("temperature"))) {
    uint32_t color = temp.color(tem, 255);//temp to RGB
    fillStrip(color);  
    decode32BitColor(color);
  }
  else {

    fillStrip(hsl(hue, sat, 50)); //hsl to RGB
  }
}

void doRainbow () {
  ticker.detach();
  ticker.attach_ms(20, rainbowAmimation); //do not set period to low or it will reset
}

void xmas(){
  ticker.detach();
  ticker.attach_ms(1000, xmasToggle); //do not set period to low or it will reset
}

uint8_t charLimitCorrection(int charValue) {
  if (charValue > 255) {
    charValue = 255;
  }
  if (charValue < 0) {
    charValue = 0;
  }
  return charValue;
}
