# Contour Synthesizer

Open instrument using ease of arduino and power of ESP32 and natural wood as sound generation surface.

HARDWARE

- Keyboard pcb (Fritzing folder)
- Control pcb
- Cnc milled pcb for gui and synth

DAC Connections
  pcm5102 -> ESP32
  vcc -> 5v
  3.3v (to dac's XMT)
  GND -> GND
  BCK -> 33
  DIN -> 26
  LCK -> 25
  FMT -> GND

SOFTWARE

- Arduino (Control board)
- FAUST (DSP)

BOM

- ESP32 DevkitC (https://www.espressif.com/en/products/devkits/esp32-devkitc/overview)
- Arduino Mega 2560 PRO
- CJMCU-5102 DAC https://pl.aliexpress.com/i/32946672788.html
- Acoustic activator (to be chosen)
- Mono amplifier (to be chosen)
- MPR121 touch chips for UI
- Induction charger / battery

ENCLOSURE

- Plywood box (design files shortly)
- Cutting template

![alt text](https://github.com/reverbrick/contour/blob/main/contour_the_begining.png?raw=true)

![alt text](https://github.com/reverbrick/contour/blob/main/golden_ratio.png?raw=true)
