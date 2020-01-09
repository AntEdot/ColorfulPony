//To intsall the board http://arduino.esp8266.com/stable/package_esp8266com_index.json

#ifdef __AVR__
#include <avr/power.h>
#endif
#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <Homey.h>      //https://github.com/athombv/homey-arduino-library/blob/master/docs/usage.md#the-basics
#include <tempcolor.h>  //https://gitlab.com/tllado/tempcolor
#include <Ticker.h>     //https://circuits4you.com/2018/01/02/esp8266-timer-ticker-example/
#include <EEPROM.h>     //https://github.com/esp8266/Arduino/tree/master/libraries/EEPROM/examples

#define NUM_LEDS 463
#define LED_PIN 12 //GPIO 12 is D6 --> https://www.roboshala.com/nodemcu-pinout/

//Neopixel init(NUM_LEDS, PIN, display spec.)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

const char* ssid = "Penthouse";
const char* password = "P3n7h0u53";
const char* deviceName = "colorfulPony";

String prevInputStr;

struct LED {
  uint8_t R;
  uint8_t G;
  uint8_t B;
};

struct store {
  String action;
  struct LED color;
  uint8_t brightness;
};

struct store memory;

uint8_t rbCounter = 0;

Ticker ticHomey;
Ticker ticker;
