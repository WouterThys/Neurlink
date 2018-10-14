/*Program to send SMS from ESP8266 via IFTTT.
 * For complete detials visit: www.circuitdigest.com
 * EXAMPLE URL: (do not use This)
 *  https://maker.ifttt.com/trigger/ESP/with/key/b8h22xlElZvP27lrAXS3ljtBa0092_aAanYN1IXXXXX
 *  
 */

#include "Network.h"
#include "Leds.h"

Leds leds;
Network nw(leds);
bool goodToGo = false;
int state = 0;
int blinkCount = 0;

const String val1 = "Hallo alles goed hier";
const String val2 = "Met vosje is ook alles goed";
const String val3 = "HELP!!";

void setup() {

  #ifdef DEBUG
  Serial.begin(115200);
  delay(500);
  Serial.println("Start");
  #endif

  // Network
  goodToGo = nw.connectNetwork(); 

  // Interrupts
  state = 0;
  pinMode(2, INPUT);
  attachInterrupt(digitalPinToInterrupt(5), button1, FALLING);
  pinMode(4, INPUT);
  attachInterrupt(digitalPinToInterrupt(4), button2, FALLING);
  pinMode(5, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), button3, FALLING);
}

void loop() {

  if (goodToGo) {
    blinkCount++;
  }

  if (blinkCount >= 20) {
    leds.ledBlink();
    blinkCount = 0;
  }
  
  if (state > 0) {

    if (goodToGo) {
      switch(state) {
        case 0: break;
        case 1: nw.makeMagic(val1);   break;
        case 2: nw.makeMagic(val2);   break;
        case 3: nw.makeMagic(val3);   break;
      }
    } else {
      leds.ledConnected(false);
      goodToGo = nw.connectNetwork(); 
    }
    state = 0;
  }
  delay(50);
}

void button1() {
 state = 1; 
}

void button2() {
  state = 2;
}

void button3() {
  state = 3;
}
