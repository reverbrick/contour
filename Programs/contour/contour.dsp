import("stdfaust.lib");
freq = hslider("freq",440,0,2000,0.0001);// : si.smoo;
bend = hslider("bend",0,0,1,0.01);// : si.smoo;
detune1 = hslider("detune1",0,0,1,0.01);// : si.smoo;
detune2 = hslider("detune2",0,0,1,0.01);// : si.smoo;
ctFreq = hslider("cutoff",10000,50,10000,0.01);// : si.smoo;
q = hslider("q",1,1,30,0.1) : si.smoo;
gain = hslider("gain",1,0,1,0.01) : si.smoo;
duty = hslider("duty",0.5,0,1,0.01) : si.smoo;
release = hslider("release",0.2,0,5,0.01) : si.smoo;
gate = button("gate");// : si.smoo;
drone = checkbox("drone");

osc1 = os.pulsetrain(freq+bend+detune1,duty) * 0.5;
osc2 = os.square(freq+bend+detune2) * 0.5;
flt1 = fi.resonlp(ctFreq,q,gain);
amp1 = en.smoothEnvelope(release,gate)+drone;
process = osc1+osc2 : flt1*amp1;
