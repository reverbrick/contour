#include "scales.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "contour.h"
#include <M5Core2.h>


#define CONFIG_I2S_BCK_PIN 12
#define CONFIG_I2S_LRCK_PIN 0
#define CONFIG_I2S_DATA_PIN 2
#define CONFIG_I2S_DATA_IN_PIN 34

#define Speak_I2S_NUMBER I2S_NUM_0

#define MODE_MIC 0
#define MODE_SPK 1
#define DATA_SIZE 1024

contour synth(44100,8);
TFT_eSprite disp(&M5.Lcd);

bool InitI2SSpeakOrMic(int mode)
{

    esp_err_t err = ESP_OK;

    i2s_driver_uninstall(Speak_I2S_NUMBER);
    i2s_config_t i2s_config = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER),
        .sample_rate = 44100,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT, // is fixed at 12bit, stereo, MSB
        .channel_format = I2S_CHANNEL_FMT_ONLY_RIGHT,
        .communication_format = I2S_COMM_FORMAT_I2S,
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
        .dma_buf_count = 2,
        .dma_buf_len = 128,
    };

    i2s_config.mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX);
    i2s_config.use_apll = false;
    i2s_config.tx_desc_auto_clear = true;
    err += i2s_driver_install(Speak_I2S_NUMBER, &i2s_config, 0, NULL);

    i2s_pin_config_t tx_pin_config;

    tx_pin_config.bck_io_num = CONFIG_I2S_BCK_PIN;
    tx_pin_config.ws_io_num = CONFIG_I2S_LRCK_PIN;
    tx_pin_config.data_out_num = CONFIG_I2S_DATA_PIN;
    tx_pin_config.data_in_num = CONFIG_I2S_DATA_IN_PIN;
    err += i2s_set_pin(Speak_I2S_NUMBER, &tx_pin_config);
    err += i2s_set_clk(Speak_I2S_NUMBER, 44100, I2S_BITS_PER_SAMPLE_16BIT, I2S_CHANNEL_STEREO);

    return true;
}

void setup() {
  M5.begin();
  M5.Axp.SetSpkEnable(true);
  InitI2SSpeakOrMic(MODE_SPK);
  M5.Lcd.fillScreen(BLACK);
  //synth
  synth.start();
  synth.setParamValue("gate",0);
  synth.setParamValue("cutoff",10000);
  synth.setParamValue("q",5);
  synth.setParamValue("duty",0.5);
  synth.setParamValue("bend",0);
  synth.setParamValue("release",1);
  synth.setParamValue("detune",0.2);
}

void circle(Point p, uint16_t c) {
  synth.setParamValue("cutoff",p.x*2);
  synth.setParamValue("detune1",p.y*2);
  if(c==WHITE){
    synth.setParamValue("gate",1);  
  }
  else{
    synth.setParamValue("gate",0);
  }
  M5.Lcd.drawCircle(p.x, p.y, 40, c);
}

void loop() {
  M5.update();
  Event& e = M5.Buttons.event;
  //synth.setParamValue("detune1",e.finger);
  if (e & (E_MOVE | E_RELEASE)) circle(e & E_MOVE ? e.from : e.to, BLACK);
  if (e & (E_TOUCH | E_MOVE)) circle(e.to, e.finger ? YELLOW : WHITE);  
}
