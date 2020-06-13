#include <TaskScheduler.h>

#include <DigitalOutput.h>

#include <LiquidCrystal_I2C.h>

#include "Constants.h"
#include "Relay.h"
#include "BleInterface.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);

Relay relay(latchPin, clockPin, dataPin);

Scheduler runner;

void onBleConnected(bool isConnected) {
  if(isConnected) {
    relay.setOutputs(PUMPS[0]);
  }
  else {
    relay.setOutputs(0);
  }
}

void onBleWrite(String value) {
  // set cursor to first column, first row
  lcd.clear();
  // print message
  lcd.print(value);
}

void setup() {
  Serial.begin(115200);

  Serial.println("Boot complete");

  new BleInterface(LED, &onBleConnected, &onBleWrite);
  
  // initialize LCD
  lcd.init();
  // turn on LCD backlight                      
  lcd.backlight();

  runner.init();

  Serial.println("Setup complete");

  lcd.clear();
  lcd.print("READY");
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);
}
