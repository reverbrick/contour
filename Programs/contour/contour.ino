#include "scales.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "contour.h"
#include <Wire.h>
#include "Adafruit_MPR121.h"
#include <Trill.h>

Adafruit_MPR121 cap = Adafruit_MPR121();
Adafruit_MPR121 cap2 = Adafruit_MPR121();
Trill hex;
Trill bar;

int frq = 0;
float bend = 0;
float touch = 0;
float max_touch = 0;
boolean hex_on = false;
boolean bar_on = false;

contour synth(48000,8);

void setup() {
  //keyboard
  cap.begin(0x5A);
  cap2.begin(0x5C);
  cap.setThreshholds(12, 6); //touch/release - default 12/6
  cap2.setThreshholds(12, 6); //touch/release - default 12/6
  //trills
  hex.setup(Trill::TRILL_HEX);
  bar.setup(Trill::TRILL_BAR);
  //synth
  synth.start();
  synth.setParamValue("gate",0);
  synth.setParamValue("cutoff",10000);
  synth.setParamValue("q",5);
  synth.setParamValue("duty",0.5);
}

void loop() {
  hex.read();
  //getNumHorizontalTouches()
  //touchHorizontalLocation(i)
  //touchHorizontalSize(i)
  if(hex.getNumTouches() > 0) {
    //for(int i = 0; i < hex.getNumTouches(); i++) {
        //Serial.print(hex.touchLocation(i));
        //Serial.print(hex.touchSize(i));
    //}
    //todo bend scaling
    bend = hex.touchLocation(0)-900;
    hex_on = true;
  }
  else if(hex_on) {
    bend = 0;
    hex_on = false;
  }
  max_touch = 0;
  frq = 0;
  for (uint8_t i=0; i<24; i++) {
    if(i<12){
      touch = (300-cap.filteredData(i))/300.0;  
    } else {
      touch = (300-cap2.filteredData(i-12))/300.0;
    }
    if (touch>max_touch){
      max_touch = touch;
      frq = i;
    }
  }
  if(max_touch > 0.2){ //touch threshold
    synth.setParamValue("freq",note[frq+48]+bend);
    synth.setParamValue("gain",max_touch);
    synth.setParamValue("gate",1);
  } else {
    synth.setParamValue("gate",0);
  }
  bar.read();
  if(bar.getNumTouches() > 0) {
    //for(int i = 0; i < bar.getNumTouches(); i++) {
        //Serial.print(bar.touchLocation(i));
        //Serial.print(bar.touchSize(i));
    //}
    synth.setParamValue("cutoff",bar.touchLocation(0)*2);
    bar_on = true;
  }
  else if(bar_on) {
    synth.setParamValue("cutoff",10000);
    bar_on = false;
  }
}
