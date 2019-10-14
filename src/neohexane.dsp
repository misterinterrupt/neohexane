import("stdfaust.lib");

gate = button("../[0]gate") : ba.impulsify;

carrierAmpEnv(trig) = hgroup("[3]AmpEnv", en.asr(
    vslider("[0]attack",0, 0, 2, 0.001): si.smoo,
  	vslider("[1]sustain",0.8, 0.0, 1.0, 0.01): si.smoo,
    vslider("[2]release",0.25, 0, 2, 0.001): si.smoo,
    trig
  )
);
modulationEnv(trig) = hgroup("../[4]ModEnv", en.asr(
    vslider("[0]attack",0, 0, 2, 0.001): si.smoo,
  	vslider("[1]sustain", 0.7, 0.0, 1.0,0.01): si.smoo,
    vslider("[2]release",0.25, 0, 2, 0.001): si.smoo,
    trig
  )
);
envs = vgroup("../Envs", AmpEnv, modulationEnv): attach;

modulatorFreq = vslider("modulator-freq", 65, 10, 6666, 1) : si.smoo;
carrierFreq = vslider("carrier-freq", 60, 10, 6666, 10) : si.smoo;
modIndex = vslider("modulator-index", 10000, 10, 15000, 10) : si.smoo;
carrierGain = vslider("carrier-gain", 0.5, 0, 1, 0.01) : si.smoo;

dualOpFm(trig, carFreq, modFreq, ampEnv, modEnv) = (out)
with {
  modulator = os.osc(modulatorFreq);
  carrier = os.osc(carrierFreq + modulator * (modIndex * modulationEnv(trig)));
  out = hgroup("[1]Oscillators", (carrier * (carrierGain * carrierAmpEnv(trig))));
};

process = dualOpFm(gate) <: _,_;