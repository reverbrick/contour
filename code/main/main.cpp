#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

//#include <Wire.h>
#include "Adafruit_MPR121.h"

#include "WaveSynth.h"

extern "C" {
    void app_main(void);
}

void app_main(void)
{
    int SR = 48000;
    int BS = 8;
    WaveSynth synth(SR,BS);
    synth.setParamValue("gate",1);
    synth.start();

    while(1) {
        synth.setParamValue("freq",rand()%(2000-50 + 1) + 50);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
