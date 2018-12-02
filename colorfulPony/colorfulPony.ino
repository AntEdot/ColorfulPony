//https://github.com/athombv/homey-arduino-library/blob/master/docs/usage.md#the-basics

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <Homey.h>
#include <tempcolor.h> //https://gitlab.com/tllado/tempcolor
#include <Ticker.h>   //https://circuits4you.com/2018/01/02/esp8266-timer-ticker-example/

#define NUM_LEDS 463
#define LED_PIN 12 //GPIO 12 is D6 --> https://www.roboshala.com/nodemcu-pinout/

//Neopixel init(NUM_LEDS, PIN, display spec.)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

const char* ssid = "Penthouse";
const char* password = "P3n7h0u53";
const char* deviceName = "colorfulPony";

float period = 1.0;

String prevInputStr;

void setup() {
  Serial.begin(115200);
  Ticker ticker;

  strip.setBrightness(50);
  strip.begin();
  clearStrip();
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

  ticker.attach(period, tick);    //Attatch tick to the timer interupt

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

  Serial.println("READY");
}

void loop() {
}
