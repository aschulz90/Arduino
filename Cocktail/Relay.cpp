#include "Relay.h"

Relay::Relay(const int latchPin, const int clockPin, const int dataPin) {

  this->latchPin = latchPin;
  this->clockPin = clockPin;
  this->dataPin = dataPin;
  
  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  setOutputs(0);
}

void Relay::setOutputs(int value) {
  // take the latchPin low so
  // the LEDs don't change while you're sending in bits:
  digitalWrite(latchPin, LOW);
  // shift out the bits:
  shiftOut(dataPin, clockPin, MSBFIRST, ~value);

  //take the latch pin high so the LEDs will light up:
  digitalWrite(latchPin, HIGH);
}
