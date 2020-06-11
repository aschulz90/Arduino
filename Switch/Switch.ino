#include <Servo.h>

const int SERVO_ARM_MIN = 5;
const int SERVO_ARM_MAX = 110;

const int SERVO_LID_MIN = 5;
const int SERVO_LID_MAX = 110;

// constants won't change. They're used here to set pin numbers:
const int buttonPin = 3;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

Servo servo_arm;  // create servo object to control a servo
Servo servo_lid;  // create servo object to control a servo

int pos_arm = SERVO_ARM_MAX;    // variable to store the servo position
int pos_lid = SERVO_LID_MAX;    // variable to store the servo position

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT_PULLUP);

  servo_arm.attach(9);  // attaches the servo on pin 9 to the servo object
  servo_arm.write(pos_arm);

  servo_lid.attach(10);  // attaches the servo on pin 9 to the servo object
  servo_lid.write(pos_lid);
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
    if(pos_arm < SERVO_ARM_MAX) {
      pos_arm += 1;
      servo_arm.write(pos_arm);
      servo_lid.write(pos_arm);
      delay(1); 
    }
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
    if(pos_arm > SERVO_ARM_MIN) {
      pos_arm -= 1;
      servo_arm.write(pos_arm);
      servo_lid.write(pos_arm);
      delay(10); 
    }
  }
}
