#include <ESP8266WiFi.h>
#include <Arduino.h>

// WiFi connections
const char * ssid = "Waldotron3000";
const char * pass = "Panda6969";
const char * host = "maker.ifttt.com";
const int httpPort = 80;

// Variables
int value = 0;

void setup() {
  Serial.begin(115200);
  delay(100);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to: ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Netmask: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: ");
  Serial.println(WiFi.gatewayIP());

  doMagic();
}

void doMagic() {
  WiFiClient client;

  Serial.print("Connecting to: ");
  Serial.println(host);
  
  if (!client.connect(host, httpPort)) {
    Serial.println("Could not connect :(");
    return;
  }

  String data = "{";
  data.concat("\"value1\":\"");
  data.concat(578);

  client.print("POST /trigger/");
  client.print("ESP");
  client.print("/with/key/");
  client.print("bFyX52EI9t-ovFCXgFiX3X");
  client.println(" HTTP/1.1");
  client.println("Host: maker.ifttt.com");
  client.println("User-Agent: Arduino/1.0");
  client.println("Connection: close");
  client.println("Content-Type: application/json");
  client.print("Content-Length: ");
  client.println(data.length());
  client.println();
  client.println(data);
  
  Serial.println("Request send");
  // Read reply from server
  while(client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  String line = client.readStringUntil('\n');
  Serial.println("Reply was:");
  Serial.println(line);
  Serial.println();
  Serial.println("Closing connection");
  
}

void loop() {
 
}
