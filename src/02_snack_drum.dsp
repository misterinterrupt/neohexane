ba = library("basics.lib");
en = library("envelopes.lib");
os = library("oscillators.lib");
si = library("signals.lib");
no = library("noise.lib");

gate = button("../../../[0]gate");

amplitudeEnv(trig) = hgroup("[3]AmpEnv", en.asr(
    vslider("[0]attack", 0.002, 0.0, 0.333, 0.001): si.smoo,
  	vslider("[1]sustain", 0.8, 0.0, 1.0, 0.01): si.smoo,
    vslider("[2]release", 0.25, 0.0, 5, 0.001): si.smoo,
    trig
  )
);

modulationEnv(trig) = hgroup("[4]ModEnv", en.asr(
    vslider("[0]attack", 0.002, 0.0, 0.333, 0.001): si.smoo,
  	vslider("[1]sustain", 0.7, 0.0, 1.0,0.01): si.smoo,
    vslider("[2]release", 0.25, 0.0, 3, 0.001): si.smoo,
    trig
  )
);

carrierGain = vslider("[0]carrier-gain", 0.5, 0, 1, 0.01) : si.smoo;
carrierFreq = vslider("[1]carrier-freq", 60, 10, 666, 10) : si.smoo;
modulatorFreq = vslider("[2]modulator-freq", 65, 10, 1332, 1) : si.smoo;
modIndex = vslider("[3]modulator-index", 90, 10, 800, 1) : si.smoo;

dualOpFm(trig) = (out)
with {
  modulator = os.osc(modulatorFreq);
  carrier = os.osc(carrierFreq + modulator * (modIndex * modulationEnv(trig)));
  out = hgroup("[1]Oscillators", carrier * carrierGain );
};

process = dualOpFm(gate)
				 : _* amplitudeEnv(gate) * 1.5;