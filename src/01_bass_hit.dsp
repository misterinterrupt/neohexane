import("stdfaust.lib");
ba = library("basics.lib");
ef = library("misceffects.lib");
declare options "[midi:on][midi:channel 8]";

gate = button("../../../../[0][midi:keyon 41][midi: keyoff 41]gate");

amplitudeEnv(trig) = hgroup("[3]ampEnv", en.asr(
    vslider("../[1]attack", 0.002, 0.0, 0.333, 0.001): si.smoo,
  	vslider("../[2]sustain", 1.0, 0.0, 1.0, 0.01): si.smoo,
    vslider("../[3]release", 0.026, 0.0, 3, 0.001): si.smoo,
    trig
  )
);

modulationEnv(trig) = hgroup("[4]modEnv", en.asr(
    vslider("[0]attack", 0.002, 0.0, 0.333, 0.001): si.smoo,
  	vslider("[1]sustain", 0.7, 0.0, 1.0,0.01): si.smoo,
    vslider("[2]release", 0.25, 0.0, 3, 0.001): si.smoo,
    trig
  )
);

filterEnv(trig) = hgroup("[5]filtEnv", en.asr(
    vslider("[0]attack", 0.002, 0.0, 0.333, 0.001): si.smoo,
  	vslider("[1]sustain", 0.7, 0.00, 1.0,0.01): si.smoo,
    vslider("[2]release", 0.25, 0.0, 3, 0.001): si.smoo,
    trig
  )
);

combEnv(trig) = hgroup("[6]CombEnv", en.asr(
    0.02, //vslider("[0]attack", 0.002, 0.0, 0.033, 0.001): si.smoo,
  	vslider("[1]sustain", 0.7, 0.0, 1.0,0.01): si.smoo,
    vslider("[2]release", 0.25, 0.0, 3, 0.001): si.smoo,
    trig 
  )
);


carrierGain = vslider("[0]carrier-gain", 1.0, 0, 1, 0.01) : si.smoo;
carrierFreq = vslider("[1]carrier-freq", 50, 10, 666, 10) : si.smoo;
modulatorFreq = vslider("[2]modulator-freq", 85, 10, 1332, 1) : si.smoo;
modIndex = vslider("[3]modulator-index", 90, 10, 800, 1) : si.smoo;

dualOpFm(trig) = hgroup("[1]Oscillators", out)
with {
  modulator = os.osc(modulatorFreq);
  carrier = os.osc(carrierFreq + modulator * (modIndex * modulationEnv(trig)));
  out =  hgroup("fm", carrier * carrierGain), noiseGen :>_;
};

noiseGen = hgroup("[4]noise", out)
with {
  gain = vslider("[4]amp", 0.0, 0.001, 1, 0.001);
  crunch = vslider("[5]crunch", 0.001, 0.001, 1, 0.01);
  freq = vslider("[6]freq", 0.5, 0.001, 1, 0.001);
  out = no.noise * gain : ef.cubicnl_nodc(crunch, 0.8);
};

combDelay = vslider("delay", 0, 1, 512, 1);
combFeedforward = vslider("feedforward", 0.06, 0.01, 0.77, 0.01);
combResonance = vslider("resonance", 0.06, 0, 0.97, 0.01);
combMod = vslider("modulation", 0.01, 0, 256, 0.01);
comber(delay, feedforward, resonance, combMod) = (out)
with {
  del = (delay + (combMod  * (combEnv(gate) : ma.neg : _*0.5 + -0.5 ) ));
  out = fi.fb_fcomb(2048, del, feedforward, resonance);
};

lopaz = (out)
with {
  cutoff = vslider("[0]cutoff", 3000, 40, 3000, 0.01) : si.smoo;
  res = vslider("[1]resonance", 5, 1, 100, 1) : si.smoo;
  filtMod = vslider("[2]filtMod", 0.2, 0.01, 1.0, 0.01) : si.smoo;
  //why doesnt this next line work??
  f = ((filtMod * filterEnv(gate)));
  out = fi.resonlp(cutoff, res, 1.0);
};

drive = vslider("[3]drive", 0.1, 0.01, 1, 0.01);
offset =  vslider("[4]offset", 0.5, 0.01, 1, 0.01);

// compressor = (out)
// with {
//   compRatio = vslider("ratio", 4, 2, 20, 1);
//   compThreshold = vslider("threshold", -8, -80, 0, 0.25);
//   compAttack = vslider("attack", 25, 20, 80, 1);
//   compRelease = vslider("release", 100, 50, 1100, 1);
//   out = co.compressor_mono(compRatio, compThreshold, compAttack, compRelease);
// };

process = dualOpFm(gate)
				: hgroup("Comb Amp", comber(combDelay, combFeedforward, combResonance, combMod)
				: _* amplitudeEnv(gate) * 2.0)
				: hgroup("filter distortion", (ef.cubicnl(drive, offset) : lopaz))
				//  : hgroup("Compressor", compressor)
				<: _,_;


			