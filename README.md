# Volume Knob for Android
This is a simple design for a Volume controller for any Android Head unit with a USB port. Using the touch buttons is infuriating and quite dangerous, so I decided to create my own volume knob.
![20241006_235740](https://github.com/user-attachments/assets/06dbf0a0-8aaf-4327-90d1-012c1c28d321)
![20241007_002106](https://github.com/user-attachments/assets/70d0af65-9059-44f9-8eda-1e05794d7c46)

## Requirements
An Arduino Leonardo is required, but any Arduino that has HID capability works.
A 3D printer.
Standard rotary encoder.

## Wiring Layout
![electronicsDiagram](https://github.com/user-attachments/assets/92fbf004-bf83-43e3-995c-885d0477ab45)

## 3D printing the enclosure
It is best to use PLA to print the housing and knob at 0.3mm layer height. I have included the Fusion360 files I used if the sizing of your rotary encoder is different.

## The Code
Ensure that you download the required Library from here https://github.com/NicoHood/HID.
```
//Arduino Leonardo

//https://github.com/NicoHood/HID
#include "HID-Project.h"

//Pin definitions for rotary Encoder
#define outputA 7
#define outputB 6
#define press 10

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
```
