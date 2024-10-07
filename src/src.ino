//Arduino Leonardo

//https://github.com/NicoHood/HID
#include "HID-Project.h"

//Pin definitions for rotary Encoder
#define outputA 11
#define outputB 10
#define press 9

//State variables
int aState;
int aLastState;
bool pressed;

//Run on startup
void setup() {
  //Start HID Library
  Consumer.begin();

  //Rotary PinModes
  pinMode(outputA, INPUT);
  pinMode(outputB, INPUT);
  pinMode(press, INPUT);

  //Read current state
  aLastState = digitalRead(outputA);
}

//Loop
void loop() {
  //Check state
  aState = digitalRead(outputA);
  
  //If state is different, check position 
  if (aState != aLastState) {
    if (digitalRead(outputB) != aState) {
      //Twisted clockwise
      Consumer.write(MEDIA_VOLUME_UP);
    } else {
      //Twisted counter-clockwise
      Consumer.write(MEDIA_VOLUME_DOWN);
    }
  }

  //Update last state
  aLastState = aState;

  //
  if (digitalRead(press) && !pressed) {
    pressed = true;
    Consumer.write(MEDIA_VOLUME_MUTE);
    delay(100);
  }
  if (!digitalRead(press) && pressed) {
    pressed = false;
    delay(100);
  }
}