#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "bowl.h"

bowl Karplus(48000,32);

void setup() {
  Karplus.start();
}

void loop() {
 delay(1000);
}
