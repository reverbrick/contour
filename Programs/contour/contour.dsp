import("stdfaust.lib");
freq = hslider("freq",440,0,2000,0.0001) : si.smoo;
ctFreq = hslider("cutoff",500,50,10000,0.01) : si.smoo;
q = hslider("q",5,1,30,0.1) : si.smoo;
gain = hslider("gain",1,0,1,0.01) : si.smoo;
duty = hslider("duty",0.5,0,1,0.01) : si.smoo;
gate = button("gate") : si.smoo;
process = os.pulsetrain(freq,duty) * 0.5 : fi.resonlp(ctFreq,q,gain)*en.smoothEnvelope(0.2,gate);
