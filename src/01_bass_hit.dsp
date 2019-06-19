ba = library("basics.lib");
en = library("envelopes.lib");
os = library("oscillators.lib");
fi = library("filters.lib");
si = library("signals.lib");
co = library("compressors.lib");
ma = library("maths.lib");
ef = library("misceffects.lib");

gate = button("../../../../[0]gate");

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

modulatorFreq = vslider("[2]modulator-freq", 65, 10, 1332, 1) : si.smoo;
carrierFreq = vslider("[1]carrier-freq", 60, 10, 666, 10) : si.smoo;
modIndex = vslider("[3]modulator-index", 90, 10, 800, 1) : si.smoo;
carrierGain = vslider("[0]carrier-gain", 0.5, 0, 1, 0.01) : si.smoo;

dualOpFm(trig) = (out)
with {
  modulator = os.osc(modulatorFreq);
  carrier = os.osc(carrierFreq + modulator * (modIndex * modulationEnv(trig)));
  out = hgroup("[1]Oscillators", carrier * carrierGain );
};

combEnv(trig) = hgroup("CombEnv", en.asr(
    0.02, //vslider("[0]attack", 0.002, 0.0, 0.033, 0.001): si.smoo,
  	vslider("[1]sustain", 0.7, 0.0, 1.0,0.01): si.smoo,
    vslider("[2]release", 0.25, 0.0, 3, 0.001): si.smoo,
    trig 
  )
);

combDelay = vslider("delay", 0, 1, 512, 1);
combFeedforward = vslider("feedforward", 0.06, 0, 0.97, 0.01);
combResonance = vslider("resonance", 0.06, 0, 0.97, 0.01);
combMod = vslider("modulation", 0.01, 0, 256, 0.01);
comber(delay, feedforward, resonance, combMod) = (out)
with {
  del = (delay + (combMod  * (combEnv(gate) +0.01 : ma.inv ) ));
  out = hgroup("comb", fi.fb_fcomb(2048, del, feedforward, resonance));
};

compressor = (out)
with {
  compRatio = vslider("ratio", 4, 2, 20, 1);
  compThreshold = vslider("threshold", -8, -80, 0, 0.25);
  compAttack = vslider("attack", 25, 20, 80, 1);
  compRelease = vslider("release", 100, 50, 1100, 1);
  out = co.compressor_mono(compRatio, compThreshold, compAttack, compRelease);
};

lopaz = (out)
with {
  cutoff = vslider("cutoff", 250, 40, 4444, 16);
  q = vslider("q", 0.20, 0.05, 1.5, 0.01);
  gain = vslider("q", 0.20, 0.0, 1, 0.01);
  out = fi.resonlp(cutoff, q, 0.8);
};

drive = vslider("drive", 0.1, 0.01, 1, 0.01);
offset = 0.5;

process = dualOpFm(gate) 
				 : hgroup("Comb", comber(combDelay, combFeedforward, combResonance, combMod)) * 0.8 
				 : ef.cubicnl(drive,offset)
				 : _* amplitudeEnv(gate) * 1.5
				 : hgroup("", hgroup("Compressor", compressor)
				 : hgroup("Filter", lopaz))
				 <: _,_;


			