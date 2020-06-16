#include <Arduino.h>

#include <TaskScheduler.h>

#include <DigitalOutput.h>

#include <QueueList.h>

#include "BluetoothSerial.h"

#include <LiquidCrystal_I2C.h>

#include <ArduinoNvs.h>

#include <ArduinoJson.h>

#include "Constants.h"
#include "Relay.h"
//#include "BleInterface.h"

struct Ingredient {
  std::string name;
  long volume;
  long pump;
};

LiquidCrystal_I2C lcd(0x27, 16, 2);

Relay relay(latchPin, clockPin, dataPin);

Scheduler runner;

BluetoothSerial SerialBT;

DigitalOutput btConnectedLed(LED);

void onCocktailStep();

Task cocktailTask(500, TASK_FOREVER, &onCocktailStep);
QueueList <Ingredient>ingredientsQueue;
std::string cocktailName = "";

void onBtConnected(bool isConnected) {
  if(isConnected) {
    btConnectedLed.set(HIGH);
  }
  else {
    relay.setOutputs(0);
    btConnectedLed.set(LOW);
  }
}

void onBtWrite(uint8_t *data, uint8_t len) {
  if(!cocktailTask.isEnabled()) {
    DynamicJsonDocument doc(1000);
    DeserializationError error = deserializeJson(doc, data);
    if(error) {
      Serial.println(error.c_str());
      SerialBT.println(error.c_str());
    }
    else {
      if(doc.containsKey(KEY_COCKTAIL_INGEDIENTS)) {
        JsonArray ingedients = doc[KEY_COCKTAIL_INGEDIENTS];

        if(ingedients.size() > 0) {

          for(int i = 0; i < ingedients.size(); i++) {
            Ingredient ingredient = {ingedients[i][KEY_INGEDIENT_NAME], ingedients[i][KEY_INGEDIENT_VOULME], ingedients[i][KEY_INGEDIENT_PUMP]};

            ingredientsQueue.push(ingredient);
          }

          std::string name = doc[KEY_COCKTAIL_NAME];
          cocktailName = name;
          SerialBT.println(cocktailName.c_str());

          cocktailTask.restart();
        }
      }
    }
  }
}

void bt_serial_callback(esp_spp_cb_event_t event, esp_spp_cb_param_t *param){
  if(event == ESP_SPP_SRV_OPEN_EVT){
    onBtConnected(true);
  }
  else if(event == ESP_SPP_CLOSE_EVT) {
    onBtConnected(false);
  }
  else if(event == ESP_SPP_DATA_IND_EVT) {
    onBtWrite(param->data_ind.data, param->data_ind.len);
  }
}

void onCocktailStep() {
  if(ingredientsQueue.count() > 0) {
    SerialBT.println("BEGIN Task");
    Ingredient ingredient = ingredientsQueue.pop();
    long ing_volume = ingredient.volume;
    std::string ing_name = ingredient.name;

    SerialBT.print("Volume: ");
    SerialBT.println(ing_volume);
    SerialBT.print("Name: ");
    SerialBT.println(ing_name.c_str());

    lcd.clear();
    lcd.print(cocktailName.c_str());
    lcd.setCursor(0,1);
    lcd.print(ing_name.c_str());
    lcd.print(" ");
    lcd.print(ing_volume);
    lcd.print(" ml");

    relay.setOutputs(PUMPS[ingredient.pump]);

    cocktailTask.setInterval(ing_volume * PUMP_TIME_MS_PER_ML[ingredient.pump]);

    SerialBT.println("END Task");
  }
  else {
    cocktailTask.disable();
    SerialBT.println("FINISH Task");
    relay.setOutputs(0);
    lcd.clear();
    lcd.print("READY");
    return;
  }
}

void setup() {
  Serial.begin(115200);

  Serial.println("Boot complete");

  //new BleInterface(LED, &onBleConnected, &onBleWrite);
  
  // initialize LCD
  lcd.init();
  // turn on LCD backlight                      
  lcd.backlight();

  runner.init();
  runner.addTask(cocktailTask);

  SerialBT.register_callback(bt_serial_callback);
  SerialBT.begin("ESP32test"); //Bluetooth device name

  NVS.begin();

  Serial.println("Setup complete");

  lcd.clear();
  lcd.print("READY");
}

void loop() {
  runner.execute();
}
