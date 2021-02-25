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
int drone = 0;
int transp = 24;
float touch = 0;
float max_touch = 0;
boolean hex_on = false;
int hex_prg = 0;
int btn_pin[5] = {34,35,32,27};
int btn_prv[5] = {0,0,0,0};

contour synth(48000,8);

void setup() {
  //debug
  Serial.begin(115200);
  //keyboard
  cap.begin(0x5A);
  cap2.begin(0x5C);
  cap.setThreshholds(12, 6); //touch/release - default 12/6
  cap2.setThreshholds(12, 6); //touch/release - default 12/6
  //trills
  hex.setup(Trill::TRILL_HEX);
  bar.setup(Trill::TRILL_BAR);
  //buttons
  for(int i = 0; i < 4; i++) {
      pinMode(btn_pin[i], INPUT);
  }
  //synth
  synth.start();
  synth.setParamValue("gate",0);
  synth.setParamValue("cutoff",10000);
  synth.setParamValue("q",5);
  synth.setParamValue("duty",0.5);
  synth.setParamValue("bend",0);
  synth.setParamValue("release",0.2);
  synth.setParamValue("detune",0.2);
}

void loop() {
  hex.read();
  for(int i = 0; i < 4; i++) {
    if(digitalRead(btn_pin[i]) == 0 && btn_prv[i] == 0) {
      btn_prv[i] = 1;
    } else if(digitalRead(btn_pin[i]) == 0) {
      btn_prv[i] = 2;
    } else {
      btn_prv[i] = 0;
    } 
  }
  if(btn_prv[0] == 1) {
    transp = transp+12;
  }
  if(btn_prv[1] == 1) {
    hex_prg++;
  }
  if(btn_prv[3] == 1) {
    drone=not(drone);
    synth.setParamValue("drone",drone);
  }
  if(transp<=0){
    transp=0;
  }
  if(transp>=60){
    transp=0;
  }
  if(hex.getNumTouches() > 0) {
    if(hex_prg==0){
      synth.setParamValue("duty",mapfloat(hex.touchHorizontalLocation(0),0.00,1880.00,0.00,1.00));
    } else if (hex_prg==1){
      synth.setParamValue("bend",mapfloat(hex.touchLocation(0),0.00,1880.00,-130.82,130.82));
    } else if (hex_prg==2){
      synth.setParamValue("detune1",mapfloat(hex.touchLocation(0),0.00,1880.00,-130.82,130.82));
      synth.setParamValue("detune2",mapfloat(hex.touchHorizontalLocation(0),0.00,1880.00,-130.82,130.82));
    } else if (hex_prg==3){
      synth.setParamValue("release",mapfloat(hex.touchLocation(0),0.00,1880.00,0.00,5.00));
    } else {
      hex_prg = 0;
    }
    hex_on = true;
  }
  else if(hex_on) {
    if (hex_prg==1){
      synth.setParamValue("bend",0);
    }
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
    synth.setParamValue("freq",note[frq+transp]);
    synth.setParamValue("gain",max_touch);
    synth.setParamValue("gate",1);
  } else {
    synth.setParamValue("gate",0);
  }
  bar.read();
  if(bar.getNumTouches() > 0) {
    synth.setParamValue("cutoff",mapfloat(bar.touchLocation(0),0,3200,50.00,10000.00));
  }
}
