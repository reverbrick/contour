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

VirtualAnalogSynth synth(22000,16);

void setup() {
  cap.begin(0x5A);
  Serial.begin(115200);
  synth.start();
  synth.setParamValue("Sawtooth",0.0);
  synth.setParamValue("Triangle",0.0);
  synth.setParamValue("Mix Amplitude",-120.0);
  synth.setParamValue("Frequency",0.0);
  synth.setParamValue("Detuning 1",0.1);
  synth.setParamValue("Detuning 2",-0.5);
  synth.setParamValue("Saw Order",1.0);
  synth.setParamValue("Duty Cycle",0.4);
  synth.setParamValue("0x00",1.0);
  synth.setParamValue("Pink Noise",0.0);
  synth.setParamValue("Portamento",0.00100000005f);
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
      //synth.setParamValue("Detuning 1",cap.filteredData(i)/64);
      synth.setParamValue("Frequency",i+36);
      synth.setParamValue("Mix Amplitude",0.0);
    }
    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
      //synth.setParamValue("Frequency",0);
      synth.setParamValue("Mix Amplitude",-120.0);
    }
  }

  // reset our state
  lasttouched = currtouched;
/*
  // debugging info, what
  Serial.print("\t\t\t\t\t\t\t\t\t\t\t\t\t 0x"); Serial.println(cap.touched(), HEX);
  Serial.print("Filt: ");
  for (uint8_t i=0; i<12; i++) {
    Serial.print(cap.filteredData(i)); Serial.print("\t");
  }
  Serial.println();
  Serial.print("Base: ");
  for (uint8_t i=0; i<12; i++) {
    Serial.print(cap.baselineData(i)); Serial.print("\t");
  }
  Serial.println();
*/ 

}
