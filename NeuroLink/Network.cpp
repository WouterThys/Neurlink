#include "Arduino.h"
#include "Network.h"

#define MAX_RETRY 20
#define NUM_CREDENTIALS 3

const char * credentials[NUM_CREDENTIALS][2] = {
  {"Waldotron3000", "Panda6969"},
  {"Waldotron4000", "waldotron"},
  {"Test", "Test"}
  };

const char* host = "maker.ifttt.com";
const char* key = "bFyX52EI9t-ovFCXgFiX3X";
const char* event = "ESP2";
const int port = 80;

Network::Network(Leds leds) {
  _leds = leds;
}

bool Network::connectNetwork() {

  bool ok = false;
  int credential = 0;
  while (!ok && credential < NUM_CREDENTIALS) {
     ok = tryConnect(credentials[credential][0], credentials[credential][1]);
     credential++;
  }

  delay(500);
  Serial.println("");
  if (ok) {
    _leds.ledConnected(true);
    #ifdef DEBUG
    Serial.print("WiFi connected!");   
    #endif
    return true;
  } else {
    _leds.ledConnected(false);

    return false;
  }
}

bool Network::tryConnect(const char* ss, const char* pa) {

    #ifdef DEBUG
    Serial.print("Try connect to: ");
    Serial.println(ss);
    #endif

  int tryCount = 0;
  WiFi.begin(ss, pa);

//  IPAddress ip(192,168,0,117);
//  IPAddress dns(195,130,130,4);
//  IPAddress msk(255,255,255,0);
//  IPAddress gtw(192,168,0,1);
//  WiFi.config(ip,gtw, msk);
  
  int stat = WL_IDLE_STATUS;
  while (tryCount < MAX_RETRY && stat != WL_CONNECTED) {
    _leds.ledConnecting();
    tryCount++;
    stat = WiFi.status();

    #ifdef DEBUG
    Serial.print("Try: ");
    Serial.println(tryCount);
    Serial.print("Status: ");
    Serial.println(stat);
    #endif
  }

  #ifdef DEBUG
  if (tryCount < MAX_RETRY) {
    Serial.print("Connected to: ");
    Serial.println(ss);
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
    Serial.print("Gateway: ");
    Serial.println(WiFi.gatewayIP());
    Serial.print("Subnet mask: ");
    Serial.println(WiFi.subnetMask());
  } else {
    Serial.print("Failed to connect to: ");
    Serial.println(ss);
  }
  #endif

  return tryCount < MAX_RETRY;

//  if (tryCount >= MAX_RETRY) {
//
//    IPAddress ip = WiFi.localIP();
//    IPAddress msk = WiFi.subnetMask();
//    IPAddress gtw = WiFi.gatewayIP();
//
//    if (ip[3] < 50 || ip[3] > 250) {
//      ip[3] = 50;
//    } else {
//      ip[3]++;
//    }
//    
//    WiFi.config(ip, msk, gtw);
//    
//    #ifdef DEBUG
//    Serial.print("Retry with new IP address: ");
//    Serial.println(WiFi.localIP());
//    #endif
//    
//    tryCount = 0;
//    WiFi.begin(ss, pa);
//    while (tryCount < MAX_RETRY && WiFi.status() != WL_CONNECTED) {
//      _leds.ledConnecting();
//      tryCount++;
//    } 
//    return tryCount < MAX_RETRY;
//  } else {
//    return true;
//  }
//  WiFi.disconnect();
//  return false;
}

void Network::makeMagic(String value) {
  WiFiClient client;
//  Serial.print("connecting to ");
//  Serial.println(host);
  _leds.ledProgress(1);
  if (!client.connect(host, port)) {
//    Serial.println("connection failed");
    _leds.ledConnected(false);
    return;
  }

  _leds.ledProgress(2);
  int len = 7 + value.length();
  String url = "/trigger/";
          url +=event;
          url +="/with/key/";
          url += key;

//  Serial.print("Requesting URL: ");
//  Serial.println(url);
  client.print(String("POST ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Content-Type: application/x-www-form-urlencoded\r\n" +
               "Content-Length: " + len + "\r\n\r\n" +
               "value1=" + value + "\r\n");
  _leds.ledProgress(3);
  Serial.println("request sent");

  while(client.connected()) {
    if (client.available()) {
      String line = client.readStringUntil('\n');
      if (line == "\r") {
        break;
      }
    } else {
      // Wait until data is available
      delay(50); 
    }
  }

  _leds.ledProgress(4);
  String line = client.readStringUntil('\n');
  #ifdef DEBUG
  Serial.println("Response: ");
  Serial.print(line);
  #endif
  _leds.ledParty();

}
