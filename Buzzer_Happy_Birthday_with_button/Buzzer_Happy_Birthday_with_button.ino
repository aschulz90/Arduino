#include "pitches.h"  //add note library

//notes in the melody
int melody[]={
  NOTE_G4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_C5, NOTE_B4, 0,
  NOTE_G4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_D5, NOTE_C5, 0,
  NOTE_G4, NOTE_G4, NOTE_G5, NOTE_E5, NOTE_C5, NOTE_B4, NOTE_A4, 
  0,       NOTE_F5, NOTE_F5, NOTE_E5, NOTE_C5, NOTE_D5, NOTE_C5
  };

//digital pin 12 is attached to a button and here we name it
const int buttonPin= 2;
const int ledPin =  13;      // the number of the LED pin

//note durations. 4=quarter note / 8=eighth note
int noteDurations[]={4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 4};

void setup(){

  //make the button's pin input
  pinMode(buttonPin, INPUT);
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
}

void loop(){

  //read the input pin
  int buttonState = digitalRead(buttonPin);

  //if the button is pressed
  if (buttonState == 1){

    //play the notes of the melody. The 28 reresent the number of notes played in the song.
    for (int thisNote=0; thisNote <28; thisNote++){

      if(thisNote % 2 == 0) {
        digitalWrite(ledPin, HIGH);
      }
      else {
        digitalWrite(ledPin, LOW);
      }

      //to calculate the note duration, take one second. Divided by the note type
      int noteDuration = 1000 / noteDurations [thisNote];
      tone(7, melody [thisNote], noteDuration);

      //to set the speed of the song set a minimum time between notes
      int pauseBetweenNotes = noteDuration * 1.5;
      delay(pauseBetweenNotes);
    }
  }
}
