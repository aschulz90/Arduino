// See the following for generating UUIDs:
// https://www.uuidgenerator.net/
#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

#define KEY_COCKTAIL_NAME "name"
#define KEY_COCKTAIL_INGEDIENTS "ingredients"
#define KEY_INGEDIENT_NAME "name"
#define KEY_INGEDIENT_PUMP "pump"
#define KEY_INGEDIENT_VOULME "volume"

const int LED = 2;

//Pin connected to ST_CP of 74HC595
const int latchPin = 14;
//Pin connected to SH_CP of 74HC595
const int clockPin = 12;
////Pin connected to DS of 74HC595
const int dataPin = 27;

const int PUMPS[] = {
  1,
  2,
  4,
  8,
  16,
  32,
  64,
  128  
};

const double PUMP_TIME_MS_PER_ML[] = {
  50.0,
  50.0,
  50.0,
  50.0,
  50.0,
  50.0,
  50.0,
  50.0  
};
