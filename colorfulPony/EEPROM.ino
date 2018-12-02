void storeInStruct(String str, uint8_t R, uint8_t G, uint8_t B, uint8_t brightness) {
  storeInStruct(str);
  storeInStruct(R, G, B);
  storeInStruct(brightness);
}

void storeInStruct(String str) {
  memory.action = str;
}

void storeInStruct(uint8_t R, uint8_t G, uint8_t B) {
  memory.color.R = R;
  memory.color.G = G;
  memory.color.B = B;
}

void storeInStruct(uint8_t brightness) {
  memory.brightness = brightness;
}

void printEEPROM() {
  EEPROM.get(0, memory);
  Serial.print(memory.color.R);
  Serial.print(" ");
  Serial.print(memory.color.G);
  Serial.print(" ");
  Serial.println(memory.color.B);
  Serial.println(memory.brightness);
}


