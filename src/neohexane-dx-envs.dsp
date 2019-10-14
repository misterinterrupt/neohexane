import("stdfaust.lib");

gate = button("../gate");

carrierAmpEnv(trig) = hgroup("[0]AmpEnv", en.dx7envelope(
    vslider("ampenv/[0]amp-rate1",0,0,2,0.001): si.smoo,
    vslider("ampenv/[2]amp-rate2",0.02,0,2,0.001): si.smoo,
    vslider("ampenv/[4]amp-rate3",0.04,0,2,0.001): si.smoo,
    vslider("ampenv/[6]amp-rate4",0.25,0,2,0.001): si.smoo,
    vslider("ampenv/[1]amp-level1",1,0,1,0.01): si.smoo,
    vslider("ampenv/[3]amp-level2",1,0,1,0.01): si.smoo,
    vslider("ampenv/[5]amp-level3",0.5,0,1,0.01): si.smoo,
    vslider("ampenv/[7]amp-level4",0,0,1,0.01): si.smoo,
    trig
  )
);
modulationEnv(trig) = hgroup("[1]ModEnv", en.dx7envelope(
    vslider("modenv/[0]mod-rate1",0.00,0,2,0.001): si.smoo,
    vslider("modenv/[2]mod-rate2",0.02,0,2,0.001): si.smoo,
    vslider("modenv/[4]mod-rate3",0.04,0,2,0.001): si.smoo,
    vslider("modenv/[6]mod-rate4",0.25,0,2,0.001): si.smoo,
    vslider("modenv/[1]mod-level1",1,0,1,0.01): si.smoo,
    vslider("modenv/[3]mod-level2",1,0,1,0.01): si.smoo,
    vslider("modenv/[5]mod-level3",0.5,0,1,0.01): si.smoo,
    vslider("modenv/[7]mod-level4",0,0,1,0.01): si.smoo,
    trig
  )
);


modulatorFreq = hslider("modulator-freq", 110, 20, 15000, 10) : si.smoo;
carrierFreq = hslider("carrier-freq", 90, 20, 15000, 10) : si.smoo;
modIndex = hslider("modulator-index", 10000, 0, 15000, 10) : si.smoo;
modGain = hslider("modulator-gain", 0.5, 0, 1, 0.01) : si.smoo;
carrierGain = hslider("carrier-gain", 0.5, 0, 1, 0.01) : si.smoo;

dualOpFm(trig, carFreq, modFreq, ampEnv, modEnv) = (out)
with {
  modulator = os.osc(modulatorFreq);
  carrier =  os.osc(carrierFreq + modulator * (modIndex * modulationEnv(trig)));
  out = ((modulator * modGain) , (carrier * (carrierGain * carrierAmpEnv(trig))));
};

process = dualOpFm(gate) <: _,_;
