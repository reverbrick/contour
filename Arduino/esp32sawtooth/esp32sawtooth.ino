#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "FaustSawtooth.h"

FaustSawtooth faustSawtooth(48000,8);

void setup() {
  
  faustSawtooth.start();
}

void loop() {
  faustSawtooth.setParamValue("freq",rand()%(2000-50 + 1) + 50);
  delay(10);
}
