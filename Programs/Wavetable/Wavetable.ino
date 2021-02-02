#include "scales.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "WaveSynth.h"
#include <Wire.h>
#include "Adafruit_MPR121.h"

#ifndef _BV
#define _BV(bit) (1 << (bit)) 
#endif

Adafruit_MPR121 cap = Adafruit_MPR121();

uint16_t lasttouched = 0;
uint16_t currtouched = 0;

WaveSynth synth(48000,8);

void setup() {
  cap.begin(0x5A);
  synth.start();
  //synth.setParamValue("A",0.0);
  //synth.setParamValue("D",0.0);
  //synth.setParamValue("S",0.0);
  //synth.setParamValue("R",0.0);
  //synth.setParamValue("bend",0.0);
  synth.setParamValue("freq",49.0);
  synth.setParamValue("lfoFreq",3.0);
  synth.setParamValue("waveTravel",0.5);
}

void loop() {
  currtouched = cap.touched();
  
  for (uint8_t i=0; i<12; i++) {
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
      synth.setParamValue("freq",note[i+36]);
      synth.setParamValue("gate",1);
    }
    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
      synth.setParamValue("gate",0);
    }
  }

  // reset our state
  lasttouched = currtouched;

}
