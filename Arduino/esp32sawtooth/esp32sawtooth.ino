#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "FaustSawtooth.h"
#include <Wire.h>
#include "Adafruit_MPR121.h"

#ifndef _BV
#define _BV(bit) (1 << (bit)) 
#endif

Adafruit_MPR121 cap = Adafruit_MPR121();

uint16_t lasttouched = 0;
uint16_t currtouched = 0;

FaustSawtooth faustSawtooth(96000,8);

void setup() {
  cap.begin(0x5A);
  faustSawtooth.start();
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
      faustSawtooth.setParamValue("freq",i*100);
    }
    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
      faustSawtooth.setParamValue("freq",0);
    }
  }

  // reset our state
  lasttouched = currtouched;

}
