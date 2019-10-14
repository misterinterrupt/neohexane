import("stdfaust.lib");
fi = library("filters.lib");

voidverb(fb1, fb2, damp, spread, drive, offset) = cubicnlDist(drive, offset) <: par(i,4,lbcf(combtuningL(i)+spread,fb1,damp))
	:> seq(i,4,fi.allpass_comb(64, allpasstuningL(i)+spread, -fb2))
with{
    origSR = 44117.64706;

    // Filters parameters
    combtuningL(0) = 1116*ma.SR/origSR : int;
    combtuningL(1) = 1188*ma.SR/origSR : int;
    combtuningL(2) = 1277*ma.SR/origSR : int;
    combtuningL(3) = 1356*ma.SR/origSR : int;

    allpasstuningL(0) = 556*ma.SR/origSR : int;
    allpasstuningL(1) = 441*ma.SR/origSR : int;
    allpasstuningL(2) = 341*ma.SR/origSR : int;
    allpasstuningL(3) = 225*ma.SR/origSR : int;
    // Lowpass Feedback Combfiler:
    // https://ccrma.stanford.edu/~jos/pasp/Lowpass_Feedback_Comb_Filter.html
    lbcf(dt, fb, damp) = (+:@(dt)) ~ (*(1-damp) : (+ ~ *(damp)) : *(fb));
};

cubicnlDist(drive,offset) = *(pregain) : +(offset) : clip(-1,1) : cubic : fi.dcblocker
with {
    pregain = pow(10.0,2*drive);
    clip(lo,hi) = min(hi) : max(lo);
    cubic(x) = x - x*x*x/3;
    postgain = max(1.0,1.0/pregain);
};


trig(j) = button("../[0]gate%j");

Hit(trig, k) = (out)
with {
  carrierAmpEnv(trig) = hgroup("[2]amp-env", en.asr(
    vslider("[0]attack",0.001, 0.001, 2, 0.001),
    vslider("[1]sustain",0.8, 0.0, 1.0, 0.01),
    vslider("[2]release",0.7, 0.001, 5, 0.001),
    trig
    )
  );
  modulationEnv(trig) = hgroup("[3]mod-env", en.asr(
    vslider("[0]attack",0.001, 0.001, 2, 0.01),
    vslider("[1]sustain", 0.7, 0.0, 1.0,0.01),
    vslider("[2]release",0.05, 0.001, 5, 0.001),
    trig
    )
  );
  combEnv(trig) = hgroup("[4]comb-env", en.asr(
    vslider("[0]attack",0.001, 0.001, 2, 0.01),
    vslider("[1]sustain", 0.7, 0.0, 1.0,0.01),
    vslider("[2]release",0.05, 0.001, 5, 0.001),
    trig
    )
  );

  carrierFreq = vslider("h:[1]osc/[0]carrier-freq", 60, 10, 6666, 10);
  modulatorFreq = vslider("h:[1]osc/[1]modulator-freq", 65, 10, 6666, 1);
  modIndex = vslider("h:[1]osc/[2]modulation", 950, 10, 15000, 10);
  

  noiz = no.no.noise;
  modulator = (os.osccos(modulatorFreq) * modIndex) * modulationEnv(trig);
  carrier = os.osccos(carrierFreq + modulator);

  carrierGain = vslider("h:[1]osc/[3]carrier-gain", 0.8, 0, 1, 0.01);
  noizGain = vslider("h:[1]osc/[4]noiz-gain", 0.1, 0, 1, 0.01);
  
// * `maxdel`: maximum delay (a power of 2)
// * `intdel`: current (integer) comb-filter delay between 0 and maxdel
// * `del`: current (float) comb-filter delay between 0 and maxdel
// * `b0`: gain applied to delay-line input and forwarded to output
// * `aN`: minus the gain applied to delay-line output before summing with the input
// 	and feeding to the delay line
  inputGain = vslider("h:[5]comb/[0]input-gain", 0, 0, 1, 0.001);
  feedbackGain = vslider("h:[5]comb/[1]feedback", 0, 0, 0.9997, 0.0001);
  combDelay = vslider("h:[5]comb/[2]delay", 0, 0, 128, 0.1);

  sig = (noiz * noizGain),(carrier * carrierGain) :> _/2 : _*carrierAmpEnv(trig) :
  fi.fbcombfilter(128, combDelay * (combEnv(trig)), feedbackGain);
  
  wet = vslider("h:[6]fx/wet-send", 0.48, 0, 1, 0.01);
  sendOut = _ <: _*(1-wet),_*wet : _,_;

  out = hgroup("Hit-%k", sig : sendOut);
};

rev = hgroup("h:[6]reverb", out)
with {
  dist = vslider("[0]distortion", 0, 0, 1, 0.01);
  offset = vslider("[1]offset", 0, 0, 1, 0.01);
  fb1 = vslider("[2]fb1", 0.992, 0.95, 0.998, 0.001);
  fb2 = vslider("[3]fb2", 0.995, 0.95, 0.998, 0.001);
  spread = vslider("[4]spread", 0.96, 0, 1, 0.01);
  damp = vslider("[5]damp", 0.15, 0, 1, 0.001);
  level = vslider("[6]level", 0.26, 0, 1, 0.01);
  out = voidverb(fb1, fb2, damp, spread, dist, offset) * level;
};

polyVoice = vgroup("",par(i, 6, tgroup("[0]TestFM", Hit(trig(i),i))) :> _/3,(_/16:rev) :> _);


process = polyVoice <: _,_;