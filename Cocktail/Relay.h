#include <Arduino.h>

class Relay {

public:
  Relay(const int latchPin, const int clockPin, const int dataPin);

  void setOutputs(int value);

private:
  int value;

  int latchPin;
  int clockPin;
  int dataPin;
};
