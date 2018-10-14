#include "Arduino.h"
#include "Leds.h"

#define LED1  16
#define LED2  14
#define LED3  12
#define LED4  13

Leds::Leds() {
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(LED4,OUTPUT);
}

void Leds::ledBlink() {
  digitalWrite(LED1, !digitalRead(LED1));
}

void Leds::ledConnecting() {
  digitalWrite(LED1, LOW); delay(50);
  digitalWrite(LED2, LOW); delay(50);
  digitalWrite(LED3, LOW); delay(50);
  digitalWrite(LED4, LOW); delay(50);
  digitalWrite(LED4, HIGH); delay(50);
  digitalWrite(LED3, HIGH); delay(50);
  digitalWrite(LED2, HIGH); delay(50);
  digitalWrite(LED1, HIGH); delay(50);
}

void Leds::ledConnected(bool success) {

  int times;
  int rate;
  if (success) {
    times = 1;
    rate = 1000;
  } else {
    times = 4;
    rate = 400;
  }
  
  int i = 0;
  while (i < times) {
    digitalWrite(LED1, LOW); 
    digitalWrite(LED2, LOW); 
    digitalWrite(LED3, LOW); 
    digitalWrite(LED4, LOW); 
    delay(rate);

    digitalWrite(LED1, HIGH); 
    digitalWrite(LED2, HIGH); 
    digitalWrite(LED3, HIGH); 
    digitalWrite(LED4, HIGH); 
    delay(rate);
    
    i++;
  }
}

void Leds::ledProgress(int progress) {
  switch (progress) {
    default:
    case 0:
      digitalWrite(LED1, HIGH); 
      digitalWrite(LED2, HIGH); 
      digitalWrite(LED3, HIGH); 
      digitalWrite(LED4, HIGH); 
    break;

    case 1:
      digitalWrite(LED1, LOW); 
      digitalWrite(LED2, HIGH); 
      digitalWrite(LED3, HIGH); 
      digitalWrite(LED4, HIGH); 
      delay(200);
    break;

    case 2:
      digitalWrite(LED1, LOW); 
      digitalWrite(LED2, LOW); 
      digitalWrite(LED3, HIGH); 
      digitalWrite(LED4, HIGH); 
      delay(200);
    break;

    case 3:
      digitalWrite(LED1, LOW); 
      digitalWrite(LED2, LOW); 
      digitalWrite(LED3, LOW); 
      digitalWrite(LED4, HIGH); 
      delay(200);
    break;

    case 4:
      digitalWrite(LED1, LOW); 
      digitalWrite(LED2, LOW); 
      digitalWrite(LED3, LOW); 
      digitalWrite(LED4, LOW); 
      delay(200);
    break;
  }
}

void Leds::ledParty() {

  int i = 0;
  while(i < 3) {
    digitalWrite(LED1, LOW); delay(50);
    digitalWrite(LED1, HIGH); delay(100);
    
    digitalWrite(LED3, LOW); delay(50);
    digitalWrite(LED3, HIGH); delay(100);
  
    digitalWrite(LED2, LOW); delay(50);
    digitalWrite(LED2, HIGH); delay(100);
    
    digitalWrite(LED4, LOW); delay(50);
    digitalWrite(LED4, HIGH); delay(100);

    i++;
  }

//  int i = 0;
//  while(i < 5) {
//    int r = random(0,4);
//
//    switch (r) {
//      case 0:
//        digitalWrite(LED1, LOW); delay(50);
//        digitalWrite(LED1, HIGH); delay(100);
//        break;
//     case 1:
//        digitalWrite(LED2, LOW); delay(50);
//        digitalWrite(LED2, HIGH); delay(100);
//        break;
//     case 2:
//        digitalWrite(LED3, LOW); delay(50);
//        digitalWrite(LED3, HIGH); delay(100);
//        break;
//     case 3:
//        digitalWrite(LED4, LOW); delay(50);
//        digitalWrite(LED4, HIGH); delay(100);
//        break;
//    }
//
//    i++;
//  }
  
}
