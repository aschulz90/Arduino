#include "BleInterface.h"
#include "Constants.h"

void BleInterface::MyCallbacks::onWrite(BLECharacteristic *pCharacteristic) {
  std::string value = pCharacteristic->getValue();

  if (value.length() > 0) {
    Serial.println("*********");
    Serial.print("New value: ");
    Serial.print(value.c_str());
    Serial.println("*********");
    parent.writeCallback(value.c_str());
  }
}

void BleInterface::MyServerCallbacks::onConnect(BLEServer* pServer) {
  BLEDevice::startAdvertising();
  Serial.println("Conntected");
  parent.connectedLed.set(HIGH);
  parent.connectedCallback(true);
};

void BleInterface::MyServerCallbacks::onDisconnect(BLEServer* pServer) {
  Serial.println("Disconnected");
  parent.connectedLed.set(LOW);
  parent.connectedCallback(false);
};

BleInterface::BleInterface(int ledPin, ConnectionCallback connectedCallback, WriteCallback writeCallback):
  connectedLed(ledPin)
{
  BLEDevice::init("MyESP32");
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks(*this));

  BLEService *pService = pServer->createService(SERVICE_UUID);

  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

  pCharacteristic->setCallbacks(new MyCallbacks(*this));

  pCharacteristic->setValue("Hello World");
  pService->start();

  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();

  this->connectedCallback = connectedCallback;
  this->writeCallback = writeCallback;
}
