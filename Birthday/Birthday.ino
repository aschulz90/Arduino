// Include the libraries:

// #define _TASK_TIMECRITICAL      // Enable monitoring scheduling overruns
#define _TASK_SLEEP_ON_IDLE_RUN // Enable 1 ms SLEEP_IDLE powerdowns between tasks if no callback methods were invoked during the pass
#define _TASK_STATUS_REQUEST    // Compile with support for StatusRequest functionality - triggering tasks on status change events in addition to time only
// #define _TASK_WDT_IDS           // Compile with support for wdt control points and task ids
// #define _TASK_LTS_POINTER       // Compile with support for local task storage pointer
// #define _TASK_PRIORITY          // Support for layered scheduling priority
// #define _TASK_MICRO_RES         // Support for microsecond resolution
// #define _TASK_STD_FUNCTION      // Support for std::function (ESP8266 and ESP32 ONLY)
// #define _TASK_DEBUG             // Make all methods and variables public for debug purposes
// #define _TASK_INLINE            // Make all methods "inline" - needed to support some multi-tab, multi-file implementations
// #define _TASK_TIMEOUT           // Support for overall task timeout
// #define _TASK_OO_CALLBACKS      // Support for dynamic callback method binding
#include <TaskScheduler.h>

// LiquidCrystal_I2C.h: https://github.com/johnrickman/LiquidCrystal_I2C
#include <Wire.h> // Library for I2C communication
#include <LiquidCrystal_I2C.h> // Library for LCD
#include "pitches.h"  //add note library

// Wiring: SDA pin is connected to A4 and SCL pin to A5.
// Connect to LCD via I2C, default address 0x27 (A0-A2 not jumpered)
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2); // Change to (0x27,16,2) for 16x2 LCD.

//Pin connected to ST_CP of 74HC595
int latchPin = 8;
//Pin connected to SH_CP of 74HC595
int clockPin = 12;
////Pin connected to DS of 74HC595
int dataPin = 11;

// pin connected to start button
const int buttonPin= 2;
// the number of the LED pin
const int ledPin =  13;

// the number of the LED pin
const int buzzerPin =  7;

//notes in the melody
int melody[]={
  NOTE_G4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_C5, NOTE_B4, 0,
  NOTE_G4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_D5, NOTE_C5, 0,
  NOTE_G4, NOTE_G4, NOTE_G5, NOTE_E5, NOTE_C5, NOTE_B4, NOTE_A4, 
  0,       NOTE_F5, NOTE_F5, NOTE_E5, NOTE_C5, NOTE_D5, NOTE_C5
  };
const int numNotes = 28;

//note durations. 4=quarter note / 8=eighth note
int noteDurations[]={4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 4};

int currentNote = 0;

Scheduler runner;

// Callback methods prototypes
void setLeds();
void showText();
void playMelody();
void showFinish();
void clearAll();

Task ledTask(500, TASK_FOREVER, &setLeds);
Task textTask(400, 41, &showText);
Task melodyTask(1, TASK_FOREVER, &playMelody);

Task finishTask(400, 35, &showFinish);
Task clearTask(5000, 2, &clearAll);

void setup() {
  // Initiate the LCD:
  lcd.init();
  lcd.backlight();
  lcd.noDisplay();

  lcd.setCursor(3, 0); // Set the cursor on the first column and first row.
  lcd.print("Alles      zum     Geburtstag,       ");
  lcd.setCursor(3, 1); //Set the cursor on the third column and the second row (counting starts at 0!).
  lcd.print("      gute     27.             Beccy!");

  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  //make the button's pin input
  pinMode(buttonPin, INPUT);
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);

  runner.init();
  runner.addTask(ledTask);
  runner.addTask(textTask);
  runner.addTask(melodyTask);
  
  delay(1000);

  ledTask.enable();
  textTask.enable();
  melodyTask.enable();

  lcd.display();
}

void loop() {
  runner.execute();
}

void showText() {
  lcd.scrollDisplayLeft();

  if(textTask.getRunCounter() == 28) {
    // cut off start of scrolling text to prevent it from re-displaying
    lcd.clear();
    lcd.print("stag,");
    lcd.setCursor(6, 1);
    lcd.print("Beccy!");
  }

  if(textTask.isLastIteration()) {
    // show finish
    runner.addTask(finishTask);
    finishTask.enable();
  }
}

void setLeds() {
  // take the latchPin low so
  // the LEDs don't change while you're sending in bits:
  digitalWrite(latchPin, LOW);
  // shift out the bits:
  shiftOut(dataPin, clockPin, MSBFIRST, random(256));

  //take the latch pin high so the LEDs will light up:
  digitalWrite(latchPin, HIGH);
}

void playMelody() {
  //to calculate the note duration, take one second. Divided by the note type
  int noteDuration = 1000 / noteDurations[currentNote];
  tone(buzzerPin, melody[currentNote], noteDuration);

  //to set the speed of the song set a minimum time between notes
  int pauseBetweenNotes = noteDuration * 1.5;
  melodyTask.setInterval(pauseBetweenNotes);

  currentNote += 1;

  if(currentNote == numNotes) {
    currentNote = 0;
  }
}

void showFinish() {

  lcd.scrollDisplayLeft();
  
  if(finishTask.isFirstIteration()) {
    lcd.clear();
    lcd.print("                Jetzt bist du auch");
  }

  if(finishTask.isLastIteration()) {

    melodyTask.disable();

    tone(buzzerPin, NOTE_C5, 2000);
    
    lcd.clear();
    lcd.setCursor(6, 0);
    lcd.print("ALT!");

    runner.addTask(clearTask);
    clearTask.enable();
  }
}

void clearAll() {
  if(clearTask.isLastIteration()) {
    ledTask.disable();
    textTask.disable();
    melodyTask.disable();
    finishTask.disable();
  
    lcd.clear();
  
    digitalWrite(latchPin, LOW);
    // shift out the bits:
    shiftOut(dataPin, clockPin, MSBFIRST, 0);
    //take the latch pin high so the LEDs will light up:
    digitalWrite(latchPin, HIGH);
  }
}
