#include <DigitalOutput.h>
#include <Arduino.h>

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#include <functional>

typedef std::function<void(bool isConnected)> ConnectionCallback;
typedef std::function<void(String value)> WriteCallback;

/**
 * Provides the bluetooth connection callbacks and notifies on a new written value to the BLE characterstic
 */
class BleInterface {

public:
  BleInterface(int ledPin, ConnectionCallback connectedCallback, WriteCallback writeCallback);

private:

  class MyCallbacks: public BLECharacteristicCallbacks {
    public:
      MyCallbacks(BleInterface& x): parent(x) {}
    
      void onWrite(BLECharacteristic *pCharacteristic);
    private:
       BleInterface&  parent;
  };

  class MyServerCallbacks: public BLEServerCallbacks {
    public:
      MyServerCallbacks(BleInterface& x): parent(x) {}
    
      void onConnect(BLEServer* pServer);
      void onDisconnect(BLEServer* pServer);
    private:
      BleInterface&  parent;
  };
  
  DigitalOutput connectedLed;

  ConnectionCallback connectedCallback;
  WriteCallback writeCallback;
  
};
