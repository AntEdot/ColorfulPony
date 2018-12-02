void printTest() {
  Serial.println();
  Serial.println("Homey print test succesful!");
  Serial.print("Value: ");
  Serial.println(Homey.value);
  Serial.println("Done");
}

void setNeoPixelBrightness() {
  int brightValue = Homey.value.toInt();
  brightValue = charLimitCorrection(brightValue);

  strip.setBrightness(brightValue);
  strip.show();

  Serial.println();
  Serial.print("Brightness charged to: ");
  Serial.println(brightValue, DEC);
}

void setNeoPixelColor() {
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
}

void setStripColor () {
  String str = Homey.value;
  Serial.println(str);
  
  if (str.equals(prevInputStr)) {
    return;
  }

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
    
    fillStrip(temp.color(tem, 255));  //temp to RGB
  }
  else {
    
    fillStrip(hsl(hue, sat, 50)); //hsl to RGB
  }
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
