Robot Audio Plugins
================


TVDistortion
===========
I started this because I miss Disto::Fx on Linux
I was thinking there should be something like that on Linux,
some dynamic distortion plug-in(whit lot of diffident clipping methods)
The idea is that you should be able to paint a distortion curve on the TV screen,
then the curve should be applied to different "smoothing" or interpolation methods and different scales


I love making noisy music, I listen to a lot of old industrial music like Cabaret Voltaire or Psychic TV.
I'm noob to programming, I know the basics, took courses in c++ when I was younger.

You are more then welcome to do whatever you want with the code, I would love to see what that would look like :)

THIS IS NOT FINISHED BUT IT CAN BE USED


TO DO

* Improve DSP

* Make all knobs and scale logarithm

* Graph reset button

* Smooth functionality

* Redesign "pixels to dsp"

* Program interpolation

* Design ui, "lable knobs"



Dependences

liblo

mesa 

jack (developed with jack2, jack1 have not been tested)

RandomMIDIcc
===========

This plugin generate and sends random midicc data. Finished to be used


Rainbow
===========

I want to make a crossover distortion plugin, that lets the user edit distortion in diffrent regions of the signal, like a rainbow. NOT FINISHED

Bark
===========

A midi triggerd compressor/gate, snappy punchy. NOT FINISHED


CreamWhipper
===========

Cubic distortion, waveshaping and saturation. Knobs will be Wet/dry(0-100%), Drive(0-100%), Threshold(0dB to -40dB), Ceiling(0dB to -40dB) and maybe a knob that would shift the frequency of the "cubic distortion funtion"
The distortion will amplify the signal like "f(x)=x^3" and add polynomial waveshaping. The signal then go thru 3 saturation algorithms A B and C. The ceiling for the
distortion and saturation and maybe a bit before the 1.0 and -1.0 values could be a extremely thin line with extreme compression. This line should not be linear and maybe
a little random. All knob use a natural log scale. NOT FINISHED


Screenshots
-----------
<b>

TVDistortion<br/>
![screenshot](https://raw.githubusercontent.com/martinbangens/TVDistortion/master/plugins/TVDistortion/snapshot1.png "TVDistortion")

![screenshot](https://raw.githubusercontent.com/martinbangens/TVDistortion/master/plugins/TVDistortion/snapshot2.png "TVDistortion")

</b>
