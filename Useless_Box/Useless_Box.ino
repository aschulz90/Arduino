#include <Servo.h>

const int SERVO_ARM_MIN = 5;
const int SERVO_ARM_MAX = 110;

const int SERVO_LID_MIN = 80;
const int SERVO_LID_MAX = 135;

// constants won't change. They're used here to set pin numbers:
const int buttonPin = 3;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

Servo servo_arm;  // create servo object to control a servo
Servo servo_lid;  // create servo object to control a servo

int pos_arm = SERVO_ARM_MAX;    // variable to store the servo position
int pos_lid = SERVO_LID_MIN;    // variable to store the servo position

int selectedMove = 0;             //move selector

int pos = 0;

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
  if (buttonState == LOW) {

    digitalWrite(ledPin, HIGH);
    
    if (selectedMove > 9) {
      selectedMove = 0;
    } //when all moves are played, repeat the moves from beginning

    if (selectedMove == 0) {
      simpleClose();
    }
    else if (selectedMove == 1) {
      simpleClose();
    }
    else if (selectedMove == 2) {
      simpleClose2();
    }
    else if (selectedMove == 3) {
      crazydoor();
    }
    else if (selectedMove == 4) {
      slow();
    }
    else if (selectedMove == 5) {
      serious();
    }
    else if (selectedMove == 6) {
      trollClose();
    }
    else if (selectedMove == 7) {
      simpleClose();
    }
    else if (selectedMove == 8) {
      matrix();
    }
    else if (selectedMove == 9) {
      sneak();
    }

    selectedMove += 1;         //swith to next move
  }
  else {
    digitalWrite(ledPin, LOW);
  }
}

// Moves

// basic move
void simpleClose()
{
  //Moving door
  for (pos = SERVO_LID_MIN; pos < SERVO_LID_MAX; pos += 3)
  {
    servo_lid.write(pos);
    delay(15);
  }

  delay(100);

  //Moving hand
  for (pos = SERVO_ARM_MAX; pos > SERVO_ARM_MIN; pos -= 4)
  {
    servo_arm.write(pos);
    delay(15);
  }

  //hiding hand
  for (pos = SERVO_ARM_MIN; pos < SERVO_ARM_MAX; pos += 4)
  {
    servo_arm.write(pos);
    delay(15);
  }

  //hiding door
  for (pos = SERVO_LID_MAX; pos >= SERVO_LID_MIN; pos -= 3)
  {
    servo_lid.write(pos);
    delay(15);
  }
}

// open and wait, then move finger and wait, then switch of and hide
void simpleClose2()
{
  //Moving door
  for (pos = SERVO_LID_MIN; pos < SERVO_LID_MAX; pos += 3)
  {
    servo_lid.write(pos);
    delay(15);
  }
  delay(800);
  //Moving hand
  for (pos = SERVO_ARM_MAX; pos > 25; pos -= 4)
  {
    servo_arm.write(pos);
    delay(15);
  }
  delay(1000);
  for (pos = 25; pos > SERVO_ARM_MIN; pos -= 4)
  {
    servo_arm.write(pos);
    delay(15);
  }

  //hiding hand
  for (pos = SERVO_ARM_MIN; pos < SERVO_ARM_MAX; pos += 5)
  {
    servo_arm.write(pos);
    delay(15);
  }

  //hiding door
  for (pos = SERVO_LID_MAX; pos >= SERVO_LID_MIN; pos -= 3)
  {
    servo_lid.write(pos);
    delay(15);
  }

}

//open door then close it many times, wait, then quickly reopen, switch off and hide.

void crazydoor()
{
  //Moving door
  for (pos = SERVO_LID_MIN; pos < SERVO_LID_MAX - 10; pos += 3)
  {
    servo_lid.write(pos);
    delay(15);
  }

  //hiding door
  for (pos = SERVO_LID_MAX - 10; pos >= SERVO_LID_MIN; pos -= 5)
  {
    servo_lid.write(pos);
    delay(15);
  }
  //Moving door
  for (pos = SERVO_LID_MIN; pos < SERVO_LID_MAX - 20; pos += 3)
  {
    servo_lid.write(pos);
    delay(15);
  }

  //hiding door
  for (pos = SERVO_LID_MAX - 20; pos >= SERVO_LID_MIN; pos -= 15)
  {
    servo_lid.write(pos);
    delay(15);
  }
  delay(700);
  //Moving door
  for (pos = SERVO_LID_MIN; pos < SERVO_LID_MAX - 10; pos += 3)
  {
    servo_lid.write(pos);
    delay(15);
  }
  delay(700);
  //hiding door
  for (pos = SERVO_LID_MAX - 10; pos >= SERVO_LID_MIN; pos -= 5)
  {
    servo_lid.write(pos);
    delay(15);
  }

  //Moving door
  for (pos = SERVO_LID_MIN; pos < SERVO_LID_MAX; pos += 8)
  {
    servo_lid.write(pos);
    delay(15);
  }

  //Moving hand
  for (pos = SERVO_ARM_MAX; pos > SERVO_ARM_MIN; pos -= 3)
  {
    servo_arm.write(pos);
    delay(15);
  }

  //hiding hand
  for (pos = SERVO_ARM_MIN; pos < SERVO_ARM_MAX; pos += 3)
  {
    servo_arm.write(pos);
    delay(15);
  }

  //hiding door
  for (pos = SERVO_LID_MAX; pos >= SERVO_LID_MIN; pos -= 15)
  {
    servo_lid.write(pos);
    delay(15);
  }
}


//open door,move finger very slowly forward and back to hiding very slowly, then quickly close door
void slow()
{
  //Moving door
  for (pos = SERVO_LID_MIN; pos < SERVO_LID_MAX; pos += 1)
  {
    servo_lid.write(pos);
    delay(30);
  }

  //Moving hand
  for (pos = SERVO_ARM_MAX; pos > SERVO_ARM_MIN; pos -= 1)
  {
    servo_arm.write(pos);
    delay(30);
  }

  //hiding hand
  for (pos = SERVO_ARM_MIN; pos < SERVO_ARM_MAX; pos += 1)
  {
    servo_arm.write(pos);
    delay(30);
  }

  //hiding door
  for (pos = SERVO_LID_MAX; pos >= SERVO_LID_MAX - 25; pos -= 1)
  {
    servo_lid.write(pos);
    delay(30);
  }
  delay(100);
  for (pos = SERVO_LID_MAX - 25; pos >= SERVO_LID_MIN; pos -= 4)
  {
    servo_lid.write(pos);
    delay(15);
  }
}

//serious

void serious() {

  //Moving door
  for (pos = SERVO_LID_MIN; pos < SERVO_LID_MAX; pos += 3)
  {
    servo_lid.write(pos);
    delay(15);
  }

  //Moving hand
  for (pos = SERVO_ARM_MAX; pos > 70; pos -= 1)
  {
    servo_arm.write(pos);
    delay(15);
  }
  delay(800);


  //hiding door
  for (pos = SERVO_LID_MAX; pos >= SERVO_LID_MAX - 20; pos -= 3)
  {
    servo_lid.write(pos);
    delay(15);
  }

  //hiding door
  for (pos = SERVO_LID_MAX - 20; pos < SERVO_LID_MAX; pos += 3)
  {
    servo_lid.write(pos);
    delay(15);
  }
  //hiding door
  for (pos = SERVO_LID_MAX; pos >= SERVO_LID_MAX - 20; pos -= 3)
  {
    servo_lid.write(pos);
    delay(15);
  }
  //hiding door
  for (pos = SERVO_LID_MAX - 20; pos < SERVO_LID_MAX; pos += 3)
  {
    servo_lid.write(pos);
    delay(15);
  }

  servo_arm.write(80);
  delay(1000);

  //Moving hand
  for (pos = 80; pos > SERVO_ARM_MIN; pos -= 4)
  {
    servo_arm.write(pos);
    delay(15);
  }

  //hiding hand
  for (pos = SERVO_ARM_MIN; pos < SERVO_ARM_MAX; pos += 4)
  {
    servo_arm.write(pos);
    delay(15);
  }


  for (pos = SERVO_LID_MAX; pos >= SERVO_LID_MIN; pos -= 1)
  {
    servo_lid.write(pos);
    delay(15);
  }
}

void trollClose() {
  //Moving door
  for (pos = SERVO_LID_MIN; pos < SERVO_LID_MAX; pos += 3)
  {
    servo_lid.write(pos);
    delay(15);
  }

  //Moving hand
  for (pos = SERVO_ARM_MAX; pos > SERVO_ARM_MIN; pos -= 4)
  {
    servo_arm.write(pos);
    delay(15);
  }
  //hiding door
  for (pos = SERVO_LID_MAX; pos >= SERVO_LID_MAX - 20; pos -= 3)
  {
    servo_lid.write(pos);
    delay(15);
  }
  delay(2000);

  for (pos = SERVO_LID_MAX - 20; pos < SERVO_LID_MAX; pos += 3)
  {
    servo_lid.write(pos);
    delay(15);
  }

  for (pos = SERVO_LID_MAX; pos >= SERVO_LID_MAX - 10; pos -= 3)
  {
    servo_lid.write(pos);
    delay(15);
  }
  for (pos = SERVO_LID_MAX - 10; pos < SERVO_LID_MAX; pos += 3)
  {
    servo_lid.write(pos);
    delay(15);
  }
  delay(500);
  //hiding hand
  for (pos = SERVO_ARM_MIN; pos < SERVO_ARM_MAX; pos += 4)
  {
    servo_arm.write(pos);
    delay(15);
  }

  //hiding door
  for (pos = SERVO_LID_MAX; pos >= SERVO_LID_MIN; pos -= 3)
  {
    servo_lid.write(pos);
    delay(15);
  }

}

void matrix()
{

  //Moving door
  for (pos = SERVO_LID_MIN; pos < SERVO_LID_MAX; pos += 3)
  {
    servo_lid.write(pos);
    delay(15);
  }

  //Moving hand
  for (pos = SERVO_ARM_MAX; pos > 50; pos -= 4)
  {
    servo_arm.write(pos);
    delay(15);
  }

  for (pos = 50; pos > SERVO_ARM_MIN; pos -= 1)
  {
    servo_arm.write(pos);
    delay(30);
  }
  delay(300);

  for (pos = SERVO_ARM_MIN; pos < SERVO_ARM_MAX; pos += 4)
  {
    servo_arm.write(pos);
    delay(10);
  }

  //hiding door
  for (pos = SERVO_LID_MAX; pos >= SERVO_LID_MIN; pos -= 3)
  {
    servo_lid.write(pos);
    delay(15);
  }

}

void sneak()
{
  //Moving door
  for (pos = SERVO_LID_MIN; pos < SERVO_LID_MAX - 10; pos += 1)
  {
    servo_lid.write(pos);
    delay(30);
  }
  delay(2000);

  //Moving hand
  for (pos = SERVO_ARM_MAX; pos > 80; pos -= 1)
  {
    servo_arm.write(pos);
    delay(30);
  }

  delay(500);

  for (pos = SERVO_LID_MAX - 10; pos < SERVO_LID_MAX; pos += 4)
  {
    servo_lid.write(pos);
    delay(15);
  }
  delay(100);

  for (pos = 80; pos > 70; pos -= 4)
  {
    servo_arm.write(pos);
    delay(15);
  }
  delay(500);
  //hiding hand
  for (pos = 70; pos < 90; pos += 4)
  {
    servo_arm.write(pos);
    delay(15);
  }
  delay(100);
  for (pos = 90; pos > 70; pos -= 4)
  {

    servo_arm.write(pos);
    delay(15);
  }
  delay(100);
  for (pos = 70; pos < 90; pos += 4)
  {
    servo_arm.write(pos);
    delay(15);
  }
  delay(100);

  for (pos = 90; pos > SERVO_ARM_MIN; pos -= 4)
  {

    servo_arm.write(pos);
    delay(15);
  }

  for (pos = SERVO_ARM_MIN; pos < SERVO_ARM_MAX; pos += 4)
  {
    servo_arm.write(pos);
    delay(15);
  }
  //hiding door
  for (pos = SERVO_LID_MAX; pos >= SERVO_LID_MIN; pos -= 3)
  {
    servo_lid.write(pos);
    delay(15);
  }
}
