/*
    Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleWrite.cpp
    Ported to Arduino ESP32 by Evandro Copercini
*/

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#include <LiquidCrystal_I2C.h>

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

const int LED = 25;

LiquidCrystal_I2C lcd(0x27, 16, 2);
String writeValue = "Hello World";

bool deviceConnected = false;

class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string value = pCharacteristic->getValue();

      if (value.length() > 0) {
        Serial.println("*********");
        Serial.print("New value: ");
        Serial.print(value.c_str());
        Serial.println();
        Serial.println("*********");
      }
      
      writeValue = value.c_str();
      // set cursor to first column, first row
      lcd.clear();
      // print message
      lcd.print(writeValue);
    }
};


class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      BLEDevice::startAdvertising();
      Serial.println("Conntected");
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      Serial.println("Disconnected");
      deviceConnected = false;
    }
};

void setup() {
  Serial.begin(115200);

  Serial.println("1- Download and install an BLE scanner app in your phone");
  Serial.println("2- Scan for BLE devices in the app");
  Serial.println("3- Connect to MyESP32");
  Serial.println("4- Go to CUSTOM CHARACTERISTIC in CUSTOM SERVICE and write something");
  Serial.println("5- See the magic =)");

  BLEDevice::init("MyESP32");
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  BLEService *pService = pServer->createService(SERVICE_UUID);

  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

  pCharacteristic->setCallbacks(new MyCallbacks());

  pCharacteristic->setValue("Hello World");
  pService->start();

  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();

  pinMode(LED, OUTPUT);

  // initialize LCD
  lcd.init();
  // turn on LCD backlight                      
  lcd.backlight();

  // set cursor to first column, first row
  lcd.clear();
  // print message
  lcd.print(pCharacteristic->getValue().c_str());
}

void loop() {
  // put your main code here, to run repeatedly:
  if(deviceConnected) {
    digitalWrite(LED, HIGH);
  }
  else {
    digitalWrite(LED, LOW);
  }
}
