#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "karplus.h"

karplus Karplus(48000,32);

void setup() {
  Karplus.start();
}

void loop() {
 Karplus.setParamValue("gate",1);
 delay(1000);
 Karplus.setParamValue("gate",0);
}
