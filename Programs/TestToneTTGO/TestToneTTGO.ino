#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "FilterSinOsc.h"

FilterSinOsc synth(96000,8);

void setup() {
  synth.start();
  synth.setParamValue("Amplitude",0);
}

void loop() {
  for(float x = 1; x<88; x=x+0.1){
   synth.setParamValue("Frequency",x);
   delay(5);
  }
}
