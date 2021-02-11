#include "scales.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "VirtualAnalogSynth.h"
#include <Wire.h>
#include "Adafruit_MPR121.h"

#ifndef _BV
#define _BV(bit) (1 << (bit)) 
#endif

Adafruit_MPR121 cap = Adafruit_MPR121();

uint16_t lasttouched = 0;
uint16_t currtouched = 0;

VirtualAnalogSynth synth(22000,8);

void setup() {
  cap.begin(0x5A);
  synth.start();
  synth.setParamValue("Sawtooth",1.0);
  synth.setParamValue("Triangle",1.0);
  synth.setParamValue("Mix Amplitude",0.0);
  synth.setParamValue("Frequency",0.0);
  synth.setParamValue("Detuning 1",0.0);
  synth.setParamValue("Detuning 2",0.0);
}

void loop() {
  /*
  for(int x = 0; x<4000; x++){
   faustSawtooth.setParamValue("freq",x);
   delay(5);
  }
  */
  currtouched = cap.touched();
  
  for (uint8_t i=0; i<12; i++) {
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
      synth.setParamValue("Frequency",i+36);
    }
    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
      synth.setParamValue("Frequency",0);
    }
  }

  // reset our state
  lasttouched = currtouched;

}
