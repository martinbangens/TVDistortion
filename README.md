DistoTV
===========
I started this because I miss Disto::Fx on Linux
I was thinking there should be something like that on Linux,
some dynamic distortion plug-in(whit lot of diffident clipping methods)

The idea is that you should be able to paint a distortion curve on the TV screen,
then the curve should be applied to a base curve like power-cosine or something to start with.

(in the future)
There could should be a menu where you can choose from different base curves and maybe see them.
Add more knobs for different distortions and make some build in “analog tape saturation VHS style”.
Characterize the filter(right now its taken from 3bandEQ). There should be different kinds of interpolation methods.
And so on..

I love making noisy music, I listen to a lot of old industrial music like Cabaret Voltaire or Psychic TV.
I'm noob to programming, I know the basics, took courses in c++ when I was younger.

You are more then welcome to do whatever you want whit the code, I would love to see what that would look like :)

This is far from done or usable.
I'm uploading the code just to show it right now.
I case I need help

TO DO

1. when mouse is hold down and wave is painted
    if I paint out of the screen to the right
     the plugin will stopp paint
     FIX ME
2. In VST mode if I close the UI Window
    the wave gets reset back to default sine wave
    FIX ME
3. Need programs activated and also states in DistrhoPluginInfo.h
4. Need some simpel distortion dsp to start with
5. analyse the code closely
6. 3 preset built-in

Screenshot
-----------
<b>

DistoTV<br/>
![screenshot](https://raw.githubusercontent.com/martinbangens/DistoTV/master/plugins/DistoTV/snapshot1.png "DistoTV")


</b>
