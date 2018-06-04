/*
  Using the ticks from a Quartz clock for triggering music

  The circuit:
  - piezo speaker on digital pin 12 and ground
  - Wires connected to quartz clock movement IC in A0 and A1
  - Ground connected to ground of negative terminal of clock AA battery compartment

  created by Charlene Atlas
  last modified 15 Apr 2018

  Example code used in this script:
  http://www.arduino.cc/en/Tutorial/AnalogInput
  http://www.arduino.cc/en/Tutorial/Tone
  https://learn.adafruit.com/adafruit-arduino-lesson-10-making-sounds/overview
*/

#include "pitches.h"

// Variables for the clock
int clockPin0 = A0;    // input pin for the first wire from the clock IC
int clockPin1 = A1;    // input pin for the second wire from the clock IC
int clockWireValue0 = 0; // for saving read value
int clockWireValue1 = 0; // for saving read value
bool isTickState = false; // for tracking state for the the first input pin being active
bool isTockState = false; // for tracking state for the the second input pin being active

// Variables for the speaker
int speakerPin = 12;

// Variables for the music
// notes in the melody:
int melody[] = {
  NOTE_E3, NOTE_D3, NOTE_C3, NOTE_D3, NOTE_E3, NOTE_E3, NOTE_E3, 0,
  NOTE_D3, NOTE_D3, NOTE_D3, 0,       NOTE_E3, NOTE_G3, NOTE_G3, 0,
  NOTE_E3, NOTE_D3, NOTE_C3, NOTE_D3, NOTE_E3, NOTE_E3, NOTE_E3, NOTE_E3, 
  NOTE_D3, NOTE_D3, NOTE_E3, NOTE_D3, NOTE_C3,  0,      0,       0
};
int noteIndex = 0;
int numNotes = 32;

void setup() {
  // declare the clock pins as an INPUT:
  pinMode(clockPin0, INPUT);
  pinMode(clockPin1, INPUT);

  // Setup serial communication
  Serial.begin(9600);

}

void loop() {

  // read new values from the clock:
  clockWireValue0 = analogRead(clockPin0);
  clockWireValue1 = analogRead(clockPin1);
  
  // Print to monitor based on values
  if(clockWireValue0 > 0 && clockWireValue1 > 0)
  {
    if(clockWireValue0 > clockWireValue1)
    {
      if(!isTickState) // If we are not in tick state already, switch to it
      {
        Serial.println("TICK");
        Serial.println("");
        playNextNote();
        isTickState = true;
        isTockState = false;
      }
    }
    if(clockWireValue1 > clockWireValue0)
    {
      if(!isTockState) // If we are not in tock state already, switch to it
      {
        Serial.println("TOCK");
        Serial.println("");
        playNextNote();
        isTockState = true;
        isTickState = false;
      }
    }
  }
}

void playNextNote(){
  // Play through melody each tick
  int note = noteIndex % numNotes;
  int nextNote = melody[note];
  tone(speakerPin, nextNote);
  delay(100);
  noTone(speakerPin);
  noteIndex = noteIndex + 1;

  /*// Same note each tick
  tone(speakerPin, NOTE_C4);
  delay(100);
  noTone(speakerPin);*/
}

