#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "FaustSawtooth.h"

FaustSawtooth faustSawtooth(96000,8);

void setup() {
  faustSawtooth.start();
}

void loop() {
  for(int x = 0; x<4000; x++){
   faustSawtooth.setParamValue("freq",x);
   delay(5);
  }
}
