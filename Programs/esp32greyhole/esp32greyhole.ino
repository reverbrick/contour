#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "greyhole.h"

greyhole Greyhole(48000,8);

void setup() {
  
  Greyhole.start();
}

void loop() {
  //faustSawtooth.setParamValue("freq",rand()%(2000-50 + 1) + 50);
  delay(10);
}
