#ifndef Leds_h
#define Leds_h

#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

class Leds {
  public:
    Leds();
    void ledBlink();
    void ledConnecting();
    void ledConnected(bool success);
    void ledProgress(int progress);
    void ledParty();
};

#endif
