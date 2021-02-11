#include "scales.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lab.h"
#include <Wire.h>
#include "Adafruit_MPR121.h"

#ifndef _BV
#define _BV(bit) (1 << (bit)) 
#endif

Adafruit_MPR121 cap = Adafruit_MPR121();

uint16_t lasttouched = 0;
uint16_t currtouched = 0;

lab synth(22000,8);

void setup() {
  cap.begin(0x5A);
  synth.start();
  //vcf
  synth.setParamValue("Bypass",0);
  //Signal Levels
  synth.setParamValue("Sawtooth",1.0);
  //Pulse Train
  //synth.setParamValue("Order 3",0.0);
  //Signal Parameters
  //synth.setParamValue("Mix Amplitude",-10.0);
  //synth.setParamValue("Frequency",49.0);
  //synth.setParamValue("lfoDepth",1.0);
  //synth.setParamValue("lfoFreq",3.0);
  //synth.setParamValue("waveTravel",0.3);
}

void loop() {
  currtouched = cap.touched();
  
  for (uint8_t i=0; i<12; i++) {
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
      synth.setParamValue("Frequency",note[i+36]);
      //synth.setParamValue("gate",1);
    }
    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
      //synth.setParamValue("gate",0);
    }
  }

  // reset our state
  lasttouched = currtouched;

}
