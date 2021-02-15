import("stdfaust.lib");
freq = hslider("fequency",440,0,2000,0.0001) : si.smoo;
ctFreq = hslider("[0]cutoffFrequency",500,50,10000,0.01) : si.smoo;
q = hslider("[1]q",5,1,30,0.1) : si.smoo;
gain = hslider("[2]gain",1,0,1,0.01) : si.smoo;
t = button("[3]gate") : si.smoo;
process = os.pulsetrain(freq,0.1) * 0.5 : fi.resonlp(ctFreq,q,gain)*t;
