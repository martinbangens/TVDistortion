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

* Redesign "graphic to dsp"

* Program interpolation

* Design ui, "lable knobs"



Dependences

liblo

mesa 

jack (developed with jack2, jack1 have not been tested)

RandomMIDIcc
===========

This plugin generate and sends random midicc data.



DigitalGainer
===========

Makes square wave of the signal and keeps the the frequencies and look at the signal frequencies as a sine waves to modulate and amplitude them to square waves. Round the corners for waves haping the signal, add extra small randomness in frequency and volume.

knob1 Gain

knob2 tone

Screenshot
-----------
<b>

TVDistortion<br/>
![screenshot](https://raw.githubusercontent.com/martinbangens/TVDistortion/master/plugins/TVDistortion/snapshot1.png "TVDistortion")

![screenshot](https://raw.githubusercontent.com/martinbangens/TVDistortion/master/plugins/TVDistortion/snapshot2.png "TVDistortion")

</b>
