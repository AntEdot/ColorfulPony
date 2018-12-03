void setup() {
  Serial.begin(115200);
  EEPROM.begin(512);
  
  strip.setBrightness(50);
  strip.begin();
  setStripToPrev();
  strip.show();

  //Connect to network
  Serial.println();
  Serial.print("Connecting..");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  //Start Homey library
  Homey.begin(deviceName);
  /* Note:
     The name of each Arduino on the network needs to be unique
     since it will be used as the unique identifier for your device.
     The name is stored as a String and can thus be as long as you
     desire it to be.
  */
  

  //Register an example action
  Homey.addAction("printTest", printTest);
  Homey.addAction("setNeoPixelBrightness", setNeoPixelBrightness);
  Homey.addAction("setNeoPixelColor", setNeoPixelColor);
  Homey.addAction("doWaveAnimation", doWaveAnimation);
  Homey.addAction("setStripBrightness", setStripBrightness);
  Homey.addAction("setStripColor", setStripColor);
  Homey.addAction("rainbow", doRainbow);

  Serial.println("READY");
}

void loop() {
  Homey.loop();
}
