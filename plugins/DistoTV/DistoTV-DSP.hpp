float tube(float sig, float gain)
{
 
  sig = sig * (2*gain);
  
  if (sig < 0.000000001f and sig > -0.000000001f){
   sig = sin(sig);
  }
  sig = sig + sin(0.000000000000000000000000001f);
  return sig;
}

float tvnoise(float sig, float knob)
{
  sig = sig +(sin(sig*0.1*knob));
  sig = sig +(sin(sig*0.01*knob));
  sig = sig +(sin(sig*0.001*knob));
  sig = sig +(sin(sig*0.00001*knob));
  return sig;
}