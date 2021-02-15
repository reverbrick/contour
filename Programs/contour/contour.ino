#include "scales.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "contour.h"
#include <Wire.h>
#include "Adafruit_MPR121.h"

#ifndef _BV
#define _BV(bit) (1 << (bit)) 
#endif

Adafruit_MPR121 cap = Adafruit_MPR121();

uint16_t lasttouched = 0;
uint16_t currtouched = 0;
uint8_t frq = 0;
uint8_t gate = 0;

contour synth(22000,16);

void setup() {
  cap.begin(0x5A);
  Serial.begin(115200);
  synth.start();
  synth.setParamValue("fequency",440.0);
  /*
  synth.setParamValue("Sawtooth",0.4);
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
  */
}

void loop() {
  currtouched = cap.touched();
  gate = 0;
  for (uint8_t i=0; i<12; i++) {
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
      //synth.setParamValue("Detuning 1",cap.filteredData(i)/64);
      frq = i;
      synth.setParamValue("gate",1.0);
    }
    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
      synth.setParamValue("gate",0.0);
    }
  }
  synth.setParamValue("fequency",cap.baselineData(frq)+note[frq+48]);

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
