/*Program to send SMS from ESP8266 via IFTTT.
 * For complete detials visit: www.circuitdigest.com
 * EXAMPLE URL: (do not use This)
 *  https://maker.ifttt.com/trigger/ESP/with/key/b8h22xlElZvP27lrAXS3ljtBa0092_aAanYN1IXXXXX
 *  
 */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>

const char* ssid = "Waldotron3000";
const char* pass = "Panda6969";

const char* host = "maker.ifttt.com";
const char* key = "bFyX52EI9t-ovFCXgFiX3X";
const char* event = "ESP2";
const int port = 80;

const String val1 = "Hallo alles goed hier";
const String val2 = "Met vosje is ook alles goed";
const String val3 = "HELP!!";

void setup() {
  Serial.begin(115200);
  Serial.println();

  connectNetwork();
  makeCall(val1);
  
}

void connectNetwork() {
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void makeCall(String value) {
  WiFiClient client;
  Serial.print("connecting to ");
  Serial.println(host);
  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    return;
  }

  int len = 7 + value.length();
  String url = "/trigger/";
          url +=event;
          url +="/with/key/";
          url += key;

  Serial.print("Requesting URL: ");
  Serial.println(url);
  client.print(String("POST ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Content-Type: application/x-www-form-urlencoded\r\n" +
               "Content-Length: " + len + "\r\n\r\n" +
               "value1=" + value + "\r\n");

  Serial.println("request sent");

  while(client.connected()) {
    if (client.available()) {
      digitalWrite(0,LOW);
      String line = client.readStringUntil('\n');
      if (line == "\r") {
        Serial.println("Headers received");
        break;
      }
    } else {
      // Wait until data is available
      delay(100); 
      digitalWrite(0,HIGH);
      delay(100); 
      digitalWrite(0,LOW);
    }
  }

  String line = client.readStringUntil('\n');
  Serial.println("Response: ");
  Serial.print(line);

  Serial.println();
  Serial.println("closing connection");
}

void loop() {
}
