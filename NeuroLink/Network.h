#ifndef Network_h
#define Network_h

#include "Arduino.h"
#include "Leds.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

//#define DEBUG

class Network {
  public:
    Network(Leds leds);
    bool connectNetwork();
    void makeMagic(String value);
  private:
    Leds _leds;
    bool tryConnect(const char* ssid, const char* pass);
};

#endif
